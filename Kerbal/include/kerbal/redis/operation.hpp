/*
 * option.hpp
 *
 *  Created on: 2018年5月29日
 *      Author: peter
 */

#ifndef SRC_REDIS_OPERATION_HPP_
#define SRC_REDIS_OPERATION_HPP_

namespace kerbal
{
	namespace redis
	{
		namespace optional_ns = std;

		class Operation
		{
			public:
				template <typename ReturnType = optional_ns::optional<std::string> >
				ReturnType get(const Context & conn, const std::string & key) const;

				template <typename ValueType>
				std::string set(const Context & conn, const std::string & key, const ValueType & value)
				{
					RedisCommand cmd("set %s %s", key, value);
					AutoFreeReply reply = cmd.excute(conn);
					switch (reply.replyType()) {
						case Redis_reply_type::STATUS:
							return reply->str;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename ValueType>
				std::string set(const Context & conn, const std::pair<std::string, ValueType> & key_value)
				{
					return set(conn, key_value.first, key_value.second);
				}

				bool del(const Context & conn, const std::string & key)
				{
					RedisCommand cmd("del %s", key);
					AutoFreeReply reply = cmd.excute(conn);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				bool exists(const Context & conn, const std::string & key) const
				{
					RedisCommand cmd("exists %s", key);
					AutoFreeReply reply = cmd.excute(conn);
					switch (reply.replyType()) {
						case Redis_reply_type::INTEGER:
							return reply->integer;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename ForwardIterator>
				bool mset(const Context & conn, ForwardIterator begin, ForwardIterator end)
				{
					std::ostringstream cmd_str;
					for (cmd_str << "mset"; begin != end; ++begin) {
						cmd_str << " " << begin->first << " " << begin->second;
					}
					RedisCommand cmd(cmd_str.str());
					AutoFreeReply reply = cmd.excute(conn);
					switch (reply.replyType()) {
						case Redis_reply_type::STATUS:
							return reply->str;
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename ValueType>
				bool mset(const Context & conn, std::map<std::string, ValueType> m)
				{
					return mset(conn, m.begin(), m.end());
				}

				template <typename ForwardIterator>
				std::vector<std::string>
				mget(const Context & conn, ForwardIterator begin, ForwardIterator end, const std::string & nil_str = "") const
				{
					std::ostringstream cmd_str;
					for (cmd_str << "mget"; begin != end; ++begin) {
						cmd_str << " " << *begin;
					}
					RedisCommand cmd(cmd_str.str());
					AutoFreeReply reply = cmd.excute(conn);
					switch (reply.replyType()) {
						case Redis_reply_type::ARRAY: {
							std::vector < std::string > res;
							res.reserve(reply->elements);
							for (size_t i = 0; i < reply->elements; ++i) {
								switch ((Redis_reply_type)(reply->element[i]->type)) {
									case Redis_reply_type::STRING:
										res.push_back(reply->element[i]->str);
										break;
									case Redis_reply_type::NIL:
										res.push_back(nil_str);
										break;
									default:
										throw RedisUnexceptedCaseException();
								}
							}
							return res;
						}
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template <typename KeyListType>
				std::vector<std::string>
				mget(const Context & conn, const KeyListType & key_list, const std::string & nil_str = "") const
				{
					return mget(conn, key_list.begin(), key_list.end(), nil_str);
				}

				std::vector<std::string>
				mget(const Context & conn, std::initializer_list<std::string> key_list, const std::string & nil_str = "") const
				{
					return mget(conn, key_list.begin(), key_list.end(), nil_str);
				}

				template <typename ReturnType>
				ReturnType hget(const Context & conn, const std::string & key, const std::string & field) const;

				std::unordered_map<std::string, std::string>
				hgetall(const Context & conn, const std::string & key) const
				{
					RedisCommand cmd("hgetall %s", key);
					AutoFreeReply reply = cmd.excute(conn);
					switch (reply.replyType()) {
						case Redis_reply_type::ARRAY: {
							std::unordered_map < std::string, std::string > res;
							res.reserve(reply->elements / 2);
							for (size_t i = 0; i < reply->elements; i += 2) {
								res[reply->element[i]->str] = reply->element[i + 1]->str;
							}
							return res;
						}
						default:
							throw RedisUnexceptedCaseException();
					}
				}

				template<typename Type = std::string>
				std::vector<Type>
				lrange(const Context & conn, const std::string & key, int start, int stop = -1) const;

		};

		template <>
		inline optional_ns::optional<std::string>
		Operation::get<optional_ns::optional<std::string> >(const Context & conn, const std::string & key) const
		{
			RedisCommand cmd("get %s", key);
			AutoFreeReply reply = cmd.excute(conn);
			switch (reply.replyType()) {
				case Redis_reply_type::STRING:
					return optional_ns::optional<std::string>(reply->str);
				case Redis_reply_type::NIL:
					return optional_ns::optional<std::string>();
				default:
					throw RedisUnexceptedCaseException();
			}
		}

		template <>
		inline std::string
		Operation::get<std::string>(const Context & conn, const std::string & key) const
		{
			optional_ns::optional res = get(conn, key);
			if (!res) {
				throw RedisNilException(key);
			}
			return *res;
		}

		template <typename ValueType>
		ValueType Operation::get(const Context & conn, const std::string & key) const
		{
			stringstream ss;
			ss << get<std::string>(conn, key);
			ValueType res;
			ss >> res;
			return res;
		}

		template <>
		inline std::string
		Operation::hget<std::string>(const Context & conn, const std::string & key, const std::string & field) const
		{
			RedisCommand cmd("hget %s %s", key, field);
			AutoFreeReply reply = cmd.excute(conn);
			switch (reply.replyType()) {
				case Redis_reply_type::STRING:
					return reply->str;
				case Redis_reply_type::NIL:
					throw RedisNilException(key + " : " + field);
				default:
					throw RedisUnexceptedCaseException();
			}
		}

		template <>
		inline std::vector<std::string>
		Operation::lrange<std::string>(const Context & conn, const std::string & key, int start, int stop) const
		{
			RedisCommand cmd("lrange %s %d %d", key, start, stop);
			AutoFreeReply reply = cmd.excute(conn);
			switch (reply.replyType()) {
				case Redis_reply_type::ARRAY: {
					std::vector<std::string> res;
					res.reserve(reply->elements);
					for (size_t i = 0; i < reply->elements; ++i) {
						res.push_back(reply->element[i]->str);
					}
					return res;
				}
				default:
					throw RedisUnexceptedCaseException();
			}
		}

		template <typename Type>
		std::vector<Type>
		Operation::lrange(const Context & conn, const std::string & key, int start, int stop) const
		{
			RedisCommand cmd("lrange %s %d %d", key, start, stop);
			AutoFreeReply reply = cmd.excute(conn);
			switch (reply.replyType()) {
				case Redis_reply_type::ARRAY: {
					std::vector<Type> res;
					res.reserve(reply->elements);
					for (size_t i = 0; i < reply->elements; ++i) {
						stringstream ss;
						ss << reply->element[i]->str;
						Type ele;
						ss >> ele;
						res.push_back(ele);
					}
					return res;
				}
				default:
					throw RedisUnexceptedCaseException();
			}
		}

	}

}

#endif /* SRC_REDIS_OPERATION_HPP_ */
