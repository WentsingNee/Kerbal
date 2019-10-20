/*
 * hash.hpp
 *
 *  Created on: 2018年12月3日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_HASH_HPP_
#define INCLUDE_KERBAL_REDIS_V2_HASH_HPP_

#include <kerbal/redis_v2/connection.hpp>
#include <kerbal/redis_v2/exception.hpp>
#include <kerbal/redis_v2/operation.hpp>
#include <kerbal/redis_v2/query.hpp>
#include <kerbal/redis_v2/reply.hpp>
#include <kerbal/redis_v2/type_traits.hpp>
#include <kerbal/type_traits/type_traits_details/enable_if.hpp>

namespace kerbal
{

	namespace redis_v2
	{

		class hash
		{
			private:
				kerbal::redis_v2::connection * bind_conn;
				std::string bind_key;

			public:

				hash(kerbal::redis_v2::connection & bind_conn, const char * bind_key) :
						bind_conn(&bind_conn), bind_key(bind_key)
				{
				}

				hash(kerbal::redis_v2::connection & bind_conn, const std::string & bind_key) :
						bind_conn(&bind_conn), bind_key(bind_key)
				{
				}

#		if __cplusplus < 201103L

				kerbal::optional::optional<std::string> hget(const kerbal::utility::string_ref & key) const
				{
					return this->hget<kerbal::optional::optional<std::string> >(key);
				}

#		endif

				template <typename ValueType
#						if __cplusplus >= 201103L
								= kerbal::optional::optional<std::string>
#						endif
				>
				typename kerbal::type_traits::enable_if<
							kerbal::optional::is_optional<ValueType>::value &&
							kerbal::redis_v2::is_redis_execute_allow_type<typename kerbal::optional::optional_traits<ValueType>::value_type>::value,
				ValueType>::type
				hget(const kerbal::utility::string_ref & field) const
				{
					kerbal::utility::string_ref args[] = { "hget", bind_key, field };
					reply _reply = bind_conn->argv_execute(begin(args), end(args));
					switch (_reply.type()) {
						case reply_type::STRING:
							return ValueType(redis_type_cast<typename ValueType::value_type>(_reply->str));
						case reply_type::NIL:
							return ValueType();
						default:
							throw unexpected_case_exception(_reply.type(), args);
					}
				}

				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						!kerbal::optional::is_optional<ValueType>::value && kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				ValueType>::type
				hget(const kerbal::utility::string_ref & field) const
				{
					kerbal::utility::string_ref args[] = { "hget", bind_key, field };
					reply _reply = bind_conn->argv_execute(begin(args), end(args));
					switch (_reply.type()) {
						case reply_type::STRING:
							return redis_type_cast<ValueType>(_reply->str);
						case reply_type::NIL:
							return ValueType();
						default:
							throw unexpected_case_exception(_reply.type(), args);
					}
				}


				template <typename ValueType>
				long long hset(const kerbal::utility::string_ref & field, const ValueType & value )
				{
					std::string str_of_value = redis_cast_to_string(value);
					kerbal::utility::string_ref argv[] = { "hset", bind_key, field, str_of_value };
					reply _reply = bind_conn->argv_execute(begin(argv), end(argv));
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), argv);
					}
				}

				/**
				 * @brief Set multiple hash fields to multiple values.
				 */
				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<typename std::iterator_traits<InputIterator>::value_type::first_type>::value &&
						kerbal::redis_v2::is_redis_execute_allow_type<typename std::iterator_traits<InputIterator>::value_type::second_type>::value,
				std::string>::type
				hmset(InputIterator begin, InputIterator end)
				{
					std::vector<std::string> argv;
					argv.push_back("hmset");
					argv.push_back(this->bind_key);
					while (begin != end) {
						argv.push_back(begin->first);
						argv.push_back(redis_cast_to_string(begin->second));
						++begin;
					}
					reply _reply = bind_conn->argv_execute(argv.begin(), argv.end());
					switch (_reply.type()) {
						case reply_type::STATUS:
							return _reply->str;
						default:
							throw unexpected_case_exception(_reply.type(), argv.begin(), argv.end());
					}
				}

#	if __cplusplus >= 201103L

				/**
				 * @brief Set multiple hash fields to multiple values.
				 */
				template <typename Type, typename ... Args>
				std::string
				hmset(const kerbal::utility::string_ref & field0, const Type & value0, Args&& ... args)
				{
					std::string argv[] = { "hmset", this->bind_key, field0, redis_cast_to_string(value0), redis_cast_to_string(args)... };
					reply _reply = bind_conn->argv_execute(begin(argv), end(argv));
					switch (_reply.type()) {
						case reply_type::STATUS:
							return _reply->str;
						default:
							throw unexpected_case_exception(_reply.type(), argv);
					}
				}

#	endif

#if KERBAL_REDIS_V2_ENABLE_CONCEPTS >= 201507L

				template <typename Container>
				static void reserve_if_could(Container &, size_t)
				{
				}

				template <Reservable Container>
				static void reserve_if_could(Container & container, size_t size)
				{
					container.reserve(size);
				}

#elif __cplusplus >= 201103L

				template <typename Container>
				static
				typename kerbal::type_traits::enable_if<!is_reservable<Container>::value>::type
				reserve_if_could(Container &, size_t)
				{
				}

				template <typename Container>
				static
				typename kerbal::type_traits::enable_if<is_reservable<Container>::value>::type
				reserve_if_could(Container & container, size_t size)
				{
					container.reserve(size);
				}

#else

				template <typename Container>
				static void reserve_if_could(Container &, size_t)
				{
				}

#endif


#		if __cplusplus >= 201103L
				template <typename ... Args>
				typename kerbal::type_traits::enable_if<
					is_redis_key_list<Args...>::value,
				std::vector<kerbal::optional::optional<std::string>>>::type
				hmget(const kerbal::utility::string_ref & key0, Args&& ... keys) const
				{
					return hmget<std::vector<kerbal::optional::optional<std::string>>>(key0, std::forward<Args>(keys)...);
				}

				template <typename ReturnType, typename ... Args>
				typename kerbal::type_traits::enable_if<
					is_redis_key_list<Args...>::value,
				ReturnType>::type
				hmget(const kerbal::utility::string_ref & key0, Args&& ... keys) const
				{
					kerbal::utility::string_ref args[] = { "hmget", this->bind_key, key0, keys... };
					reply _reply = bind_conn->argv_execute(begin(args), end(args));
					switch (_reply.type()) {
						case reply_type::ARRAY: {
							ReturnType res;
							reserve_if_could(res, _reply->elements);
							for (size_t i = 0; i < _reply->elements; ++i) {
								switch ((reply_type)(_reply->element[i]->type)) {
									case reply_type::STRING:
										res.emplace_back(_reply->element[i]->str);
										break;
									case reply_type::NIL:
										res.emplace_back();
										break;
									default:
										throw unexpected_case_exception(_reply.type(), args);
								}
							}
							return res;
						}
						default:
							throw unexpected_case_exception(_reply.type(), args);
					}
				}

				template <typename ...Types, typename ... Args>
				typename mget_tuple_return_t<1 + sizeof...(Args) - sizeof...(Types), Types...>::type
				hmget_tuple(const kerbal::utility::string_ref & field0, Args&& ... keys)
				{
					kerbal::utility::string_ref args[] = { "hmget", this->bind_key, field0, keys... };
					reply _reply = bind_conn->argv_execute(begin(args), end(args));
					switch (_reply.type()) {
						case reply_type::ARRAY: {
							typename mget_tuple_return_t<1 + sizeof...(Args) - sizeof...(Types), Types...>::type res;
							mget_helper<sizeof...(Args)>()(res, _reply, begin(args), end(args));
							return res;
						}
						default:
							throw unexpected_case_exception(_reply.type(), args);
					}
				}


#	endif


		};

	} /* namespace redis_v2 */

} /* namespace kerbal */



#endif /* INCLUDE_KERBAL_REDIS_V2_HASH_HPP_ */
