/*
 * operation.hpp
 *
 *  Created on: 2018年12月1日
 *      Author: peter
 */

#ifndef INCLUDE_KERBAL_REDIS_V2_OPERATION_HPP_
#define INCLUDE_KERBAL_REDIS_V2_OPERATION_HPP_

#include <kerbal/redis_v2/connection.hpp>
#include <kerbal/redis_v2/exception.hpp>
#include <kerbal/redis_v2/query.hpp>
#include <kerbal/redis_v2/reply.hpp>
#include <kerbal/data_struct/optional/optional.hpp>
#include <kerbal/utility/array_serve.hpp>
#include <kerbal/utility/string_ref.hpp>
#include <vector>

namespace kerbal
{

	namespace redis_v2
	{

#if __cplusplus >= 201103L

		template <typename Tp, typename = void>
		struct is_reservable : kerbal::type_traits::false_type
		{
		};

		template <typename Tp>
		struct is_reservable<Tp, decltype(std::declval<Tp>().reserve(0)) > : kerbal::type_traits::true_type
		{
		};

#endif

#ifndef KERBAL_REDIS_V2_ENABLE_CONCEPTS
#	if defined(__cpp_concepts) && (__cpp_concepts >= 201507L)
#		define KERBAL_REDIS_V2_ENABLE_CONCEPTS __cpp_concepts
#	else
#		define KERBAL_REDIS_V2_ENABLE_CONCEPTS 0
#	endif
#endif

#if KERBAL_REDIS_V2_ENABLE_CONCEPTS >= 201507L

#	if __cplusplus >= 201103L

		template <typename Container>
		concept bool Reservable = is_reservable<Container>::value;

#	else

		template <typename Container>
		concept bool Reservable = requires(Container & container, size_t size)
		{
			container.reserve(size);
		};

#	endif

#endif

		template <typename Type>
		struct is_optional : kerbal::data_struct::is_optional<Type>
		{
		};


#if __cplusplus >= 201103L

		template <int i>
		class mget_helper;

		template <>
		class mget_helper<0>
		{
				friend class operation;
				friend class hash;

				friend class mget_helper<1>;

				template <typename ...Types>
				typename std::enable_if<is_optional<
													typename kerbal::type_traits::type_chooser<0, Types...>::type
										>::value>::type
				operator()(std::tuple<Types...> & res, const reply & _reply, const kerbal::utility::string_ref * args_begin, const kerbal::utility::string_ref * args_end) const
				{
					switch ((reply_type) (_reply->element[0]->type)) {
						case reply_type::STRING:
							using ReturnType = typename std::tuple_element<0, std::tuple<Types...>>::type;
							using ele_type = typename ReturnType::value_type;
							std::get<0>(res) = redis_type_cast<ele_type>(_reply->element[0]->str);
							break;
						case reply_type::NIL:
							break;
						default:
							throw unexpected_case_exception(_reply.type(), args_begin, args_end);
					}
				}

				template <typename ...Types>
				typename std::enable_if<!is_optional<
													typename kerbal::type_traits::type_chooser<0, Types...>::type
										>::value>::type
				operator()(std::tuple<Types...> & res, const reply & _reply, const kerbal::utility::string_ref * args_begin, const kerbal::utility::string_ref * args_end) const
				{
					switch ((reply_type) (_reply->element[0]->type)) {
						case reply_type::STRING:
							using ReturnType = typename std::tuple_element<0, std::tuple<Types...>>::type;
							using ele_type = ReturnType;
							std::get<0>(res) = redis_type_cast<ele_type>(_reply->element[0]->str);
							break;
						case reply_type::NIL:
							break;
						default:
							throw unexpected_case_exception(_reply.type(), args_begin, args_end);
					}
				}
		};

		template <int i>
		class mget_helper
		{
				friend class operation;
				friend class hash;

				friend class mget_helper<i + 1> ;

				template <typename ...Types>
				typename std::enable_if<is_optional<
													typename kerbal::type_traits::type_chooser<i, Types...>::type
										>::value>::type
				operator()(std::tuple<Types...> & res, const reply & _reply, const kerbal::utility::string_ref * args_begin, const kerbal::utility::string_ref * args_end) const
				{
					switch ((reply_type) (_reply->element[i]->type)) {
						case reply_type::STRING:
							using ReturnType = typename std::tuple_element<i, std::tuple<Types...>>::type;
							using ele_type = typename ReturnType::value_type;
							std::get<i>(res) = redis_type_cast<ele_type>(_reply->element[i]->str);
							break;
						case reply_type::NIL:
							break;
						default:
							throw unexpected_case_exception(_reply.type(), args_begin, args_end);
					}

					mget_helper<i - 1>()(res, _reply, args_begin, args_end);
				}

				template <typename ...Types>
				typename std::enable_if<!is_optional<
													typename kerbal::type_traits::type_chooser<i, Types...>::type
										>::value>::type
				operator()(std::tuple<Types...> & res, const reply & _reply, const kerbal::utility::string_ref * args_begin, const kerbal::utility::string_ref * args_end) const
				{
					switch ((reply_type) (_reply->element[i]->type)) {
						case reply_type::STRING:
							using ReturnType = typename std::tuple_element<i, std::tuple<Types...>>::type;
							using ele_type = ReturnType;
							std::get<i>(res) = redis_type_cast<ele_type>(_reply->element[i]->str);
							break;
						case reply_type::NIL:
							break;
						default:
							throw unexpected_case_exception(_reply.type(), args_begin, args_end);
					}

					mget_helper<i - 1>()(res, _reply, args_begin, args_end);
				}

		};

		template <int blank, typename ...Types>
		class mget_tuple_return_t;
		
		template <int blank, typename ...Types>
		class mget_tuple_return_t : public mget_tuple_return_t<blank - 1 >= 0 ? blank - 1 : -1, Types..., kerbal::data_struct::optional<std::string>>
		{
		};

		template <typename Type0, typename ...Types>
		class mget_tuple_return_t<0, Type0, Types...>
		{
			public:
				using type = std::tuple<Type0, Types...>;
		};

		/**
		 * @brief 防止模板递归爆栈的特化
		 */
		template <typename ...Types>
		class mget_tuple_return_t<-1, Types...>
		{
		};

#endif

		class operation
		{
			private:
				connection & conn;


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

//				template <typename Type>
//				static void make_execute_args_template(std::string & templ, const kerbal::utility::string_ref &, const Type &)
//				{
//					templ += " %s ";
//					templ += placeholder_traits<Type>();
//				}
//
//				template <typename Type, typename ... Args>
//				static void make_execute_args_template(std::string & templ, const kerbal::utility::string_ref &, const Type &, Args&& ... args)
//				{
//					templ += " %s ";
//					templ += placeholder_traits<Type>();
//					make_execute_args_template(templ, std::forward<Args>(args)...);
//				}
//
//				template <typename Type, typename ... Args>
//				static std::string make_execute_args_template(const kerbal::utility::string_ref & key0, const Type & value0, Args&& ... args)
//				{
//					std::string templ;
//					make_execute_args_template(templ, key0, value0, std::forward<Args>(args)...);
//					return templ;
//				}
//
//				template <typename Type>
//				static void make_execute_args_template(std::string & templ, const std::pair<kerbal::utility::string_ref, Type> &)
//				{
//					templ += " %s ";
//					templ += placeholder_traits<Type>();
//				}
//
//				template <typename Type, typename ... Args>
//				static void make_execute_args_template(std::string & templ, const std::pair<kerbal::utility::string_ref, Type> &, Args&& ... args)
//				{
//					templ += " %s ";
//					templ += placeholder_traits<Type>();
//					make_execute_args_template(templ, std::forward<Args>(args)...);
//				}
//
//				template <typename Type, typename ... Args>
//				static std::string make_execute_args_template(const std::pair<kerbal::utility::string_ref, Type> & key_value, Args&& ... args)
//				{
//					std::string templ;
//					templ.reserve(8 + 8 * sizeof...(Args));
//					make_execute_args_template(templ, key_value, std::forward<Args>(args)...);
//					return templ;
//				}

			public:
				explicit operation(connection & conn) KERBAL_NOEXCEPT :
						conn(conn)
				{
				}

				std::string type(const kerbal::utility::string_ref & key) const
				{
					static query _query("type %s");
					reply _reply = _query.execute(conn, key.c_str());
					switch (_reply.type()) {
						case reply_type::STRING: {
							return _reply->str;
						}
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}


#		if __cplusplus < 201103L

				std::vector<std::string> keys(const kerbal::utility::string_ref & key) const
				{
					return this->get<std::vector<std::string> >(key);
				}

#		endif

				template <typename ReturnType
#						if __cplusplus >= 201103L
								= std::vector<std::string>
#						endif
				>
				ReturnType keys(const kerbal::utility::string_ref & key) const
				{
					static query _query("keys %s");
					reply _reply = _query.execute(conn, key.c_str());
					switch (_reply.type()) {
						case reply_type::ARRAY: {
							ReturnType res;
							reserve_if_could(res, _reply->elements);
							for (size_t i = 0; i < _reply->elements; ++i) {
								switch (_reply->element[i]->type) {
									case reply_type::STRING:
										res.push_back(_reply->element[i]->str);
										break;
									case reply_type::NIL:
#								if __cplusplus < 201103L
										res.push_back(typename ReturnType::value_type());
#								else
										res.emplace_back();
#								endif
										break;
									default:
										throw unexpected_case_exception(_reply.type(), _query.str());
								}
							}
							return res;
						}
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

#		if __cplusplus < 201103L

				kerbal::data_struct::optional<std::string> keys(const kerbal::utility::string_ref & key) const
				{
					return this->get<kerbal::data_struct::optional<std::string> >(key);
				}

#		endif

				template <typename ValueType
#						if __cplusplus >= 201103L
								= kerbal::data_struct::optional<std::string>
#						endif
				>
				typename kerbal::type_traits::enable_if<
							kerbal::data_struct::is_optional<ValueType>::value &&
							kerbal::redis_v2::is_redis_execute_allow_type<typename kerbal::data_struct::optional_traits<ValueType>::value_type>::value,
				ValueType>::type
				get(const kerbal::utility::string_ref & key) const
				{
					static query _query("get %s");
					reply _reply = _query.execute(conn, key.c_str());
					switch (_reply.type()) {
						case reply_type::STRING:
							return redis_type_cast<typename ValueType::value_type>(_reply->str);
						case reply_type::NIL:
							return ValueType();
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						!kerbal::data_struct::is_optional<ValueType>::value && kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				ValueType>::type
				get(const kerbal::utility::string_ref & key) const
				{
					static query _query("get %s");
					reply _reply = _query.execute(conn, key.c_str());
					switch (_reply.type()) {
						case reply_type::STRING:
							return redis_type_cast<ValueType>(_reply->str);
						case reply_type::NIL:
							return ValueType();
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				std::string>::type
				set(const kerbal::utility::string_ref & key, const ValueType & value)
				{
					static query _query(std::string("set %s ") + placeholder_traits<ValueType>());
					reply _reply = _query.execute(conn, key.c_str(), value.c_str());
					switch (_reply.type()) {
						case reply_type::STATUS:
							return _reply->str;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				template <typename KeyType, typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<KeyType>::value &&
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				std::string>::type
				set(const std::pair<KeyType, ValueType> & key_value)
				{
					return set(conn, key_value.first, key_value.second);
				}

				/**
				 * @brief Set the value of a key, only if the key does not exist.
				 */
				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				std::string>::type
				setnx(const kerbal::utility::string_ref & key, const ValueType & value)
				{
					static query _query(std::string("setnx %s ") + placeholder_traits<ValueType>());
					reply _reply = _query.execute(conn, key.c_str(), value.c_str());
					switch (_reply.type()) {
						case reply_type::STATUS:
							return _reply->str;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				/**
				 * @brief Set the value of a key, only if the key does not exist.
				 */
				template <typename KeyType, typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<KeyType>::value &&
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				std::string>::type
				setnx(const std::pair<KeyType, ValueType> & key_value)
				{
					return setnx(conn, key_value.first, key_value.second);
				}

				/**
				 * @brief Set the value and expiration of a key.
				 */
				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				std::string>::type
				setex(const kerbal::utility::string_ref & key, int seconds, const ValueType & value)
				{
					static query _query(std::string("setex %d %s ") + placeholder_traits<ValueType>());
					reply _reply = _query.execute(conn, key.c_str(), seconds, value.c_str());
					switch (_reply.type()) {
						case reply_type::STATUS:
							return _reply->str;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				/**
				 * @brief Set the value and expiration of a key.
				 */
				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				std::string>::type
				setex(const kerbal::utility::string_ref & key, const timeval & seconds, const ValueType & value)
				{
					setex(key, seconds.tv_sec, value);
				}

#	if __cplusplus >= 201103L

				/**
				 * @brief Set the value and expiration of a key.
				 */
				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				std::string>::type
				setex(const kerbal::utility::string_ref & key, std::chrono::seconds sec, const ValueType & value)
				{
					setex(key, sec.count(), value);
				}

#	endif

				/**
				 * @brief Set the value and expiration in milliseconds of a key.
				 */
				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				std::string>::type
				psetex(const kerbal::utility::string_ref & key, int millisec, const ValueType & value)
				{
					static query _query(std::string("psetex %d %s ") + placeholder_traits<ValueType>());
					reply _reply = _query.execute(conn, key.c_str(), millisec, value.c_str());
					switch (_reply.type()) {
						case reply_type::STATUS:
							return _reply->str;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				/**
				 * @brief Set the value and expiration in milliseconds of a key.
				 */
				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				std::string>::type
				psetex(const kerbal::utility::string_ref & key, const timeval & millisec, const ValueType & value)
				{
					psetex(key, millisec.tv_sec * 1000 + millisec.tv_usec / 1000, value);
				}

#	if __cplusplus >= 201103L

				/**
				 * @brief Set the value and expiration in milliseconds of a key.
				 */
				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				std::string>::type
				psetex(const kerbal::utility::string_ref & key, std::chrono::milliseconds millisec, const ValueType & value)
				{
					psetex(key, millisec.count(), value);
				}

#	endif

				/**
				 * @brief Set the string value of a key and return its old value.
				 */
				template <typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				kerbal::data_struct::optional<std::string> >::type
				getset(const kerbal::utility::string_ref & key, const ValueType & value)
				{
					return this->getset<kerbal::data_struct::optional<std::string>, ValueType >(key, value);
				}

				/**
				 * @brief Set the string value of a key and return its old value.
				 */
				template <typename ReturnType, typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::data_struct::is_optional<ReturnType>::value &&
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				ReturnType>::type
				getset(const kerbal::utility::string_ref & key, const ValueType & value)
				{
					static query _query(std::string("getset %s ") + placeholder_traits<ValueType>());
					reply _reply = _query.execute(conn, key.c_str(), value);
					switch (_reply.type()) {
						case reply_type::STRING:
							return redis_type_cast<typename ReturnType::value_type>(_reply->str);
						case reply_type::NIL:
							return ReturnType();
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				/**
				 * @brief Set the string value of a key and return its old value.
				 */
				template <typename ReturnType, typename ValueType>
				typename kerbal::type_traits::enable_if<
						!kerbal::data_struct::is_optional<ReturnType>::value &&
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				ReturnType>::type
				getset(const kerbal::utility::string_ref & key, const ValueType & value)
				{
					static query _query(std::string("getset %s ") + placeholder_traits<ValueType>());
					reply _reply = _query.execute(conn, key.c_str(), value);
					switch (_reply.type()) {
						case reply_type::STRING:
							return redis_type_cast<ReturnType>(_reply->str);
						case reply_type::NIL:
							return ReturnType();
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				/**
				 * @brief Set the string value of a key and return its old value.
				 */
				template <typename KeyType, typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<KeyType>::value &&
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				kerbal::data_struct::optional<std::string> >::type
				getset(const std::pair<KeyType, ValueType> & key_value)
				{
					return this->getset<kerbal::data_struct::optional<std::string> >(key_value.first, key_value.second);
				}

				/**
				 * @brief Set the string value of a key and return its old value.
				 */
				template <typename ReturnType, typename KeyType, typename ValueType>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<KeyType>::value &&
						kerbal::redis_v2::is_redis_execute_allow_type<ValueType>::value,
				ReturnType>::type
				getset(const std::pair<KeyType, ValueType> & key_value)
				{
					return this->getset<ReturnType, ValueType>(key_value.first, key_value.second);
				}


				/**
				 * @brief Set multiple keys to multiple values
				 */
				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<typename std::iterator_traits<InputIterator>::value_type::first_type>::value &&
						kerbal::redis_v2::is_redis_execute_allow_type<typename std::iterator_traits<InputIterator>::value_type::second_type>::value,
				std::string>::type
				mset(InputIterator begin, InputIterator end)
				{
					std::vector<std::string> argv;
					argv.push_back("mset");
					while (begin != end) {
						argv.push_back(begin->first);
						argv.push_back(redis_cast_to_string(begin->second));
						++begin;
					}
					reply _reply = conn.argv_execute(argv.begin(), argv.end());
					switch (_reply.type()) {
						case reply_type::STATUS:
						return _reply->str;
						default:
						throw unexpected_case_exception(_reply.type(), argv.begin(), argv.end());
					}
				}


#	if __cplusplus >= 201103L

				/**
				 * @brief Set multiple keys to multiple values
				 */
				template <typename Type, typename ... Args>
				std::string
				mset(const kerbal::utility::string_ref & key0, const Type & value0, Args&& ... args)
				{
					std::string argv[] = { "mset", key0, redis_cast_to_string(value0), redis_cast_to_string(args)... };
					reply _reply = conn.argv_execute(begin(argv), end(argv));
					switch (_reply.type()) {
						case reply_type::STATUS:
							return _reply->str;
						default:
							throw unexpected_case_exception(_reply.type(), argv);
					}
				}

#	endif


				/**
				 * @brief Set multiple keys to multiple values
				 */
				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<typename std::iterator_traits<InputIterator>::value_type::first_type>::value &&
						kerbal::redis_v2::is_redis_execute_allow_type<typename std::iterator_traits<InputIterator>::value_type::second_type>::value,
				long long>::type
				msetnx(InputIterator begin, InputIterator end)
				{
					std::vector<std::string> argv;
					argv.push_back("msetnx");
					while (begin != end) {
						argv.push_back(begin->first);
						argv.push_back(redis_cast_to_string(begin->second));
						++begin;
					}
					reply _reply = conn.argv_execute(argv.begin(), argv.end());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), argv.begin(), argv.end());
					}
				}

#	if __cplusplus >= 201103L

				/**
				 * @brief Set multiple keys to multiple values, only if none of the keys exist.
				 */
				template <typename Type, typename ... Args>
				long long msetnx(const kerbal::utility::string_ref & key0, const Type & value0, Args&& ... args)
				{
					std::string argv[] = { "msetnx", key0, redis_cast_to_string(value0), redis_cast_to_string(args)... };
					reply _reply = conn.argv_execute(begin(argv), end(argv));
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), argv);
					}
				}

#	endif

				std::string rename(const kerbal::utility::string_ref & key, const kerbal::utility::string_ref & newKey)
				{
					static query _query("rename %s %s");
					reply _reply = _query.execute(conn, key.c_str(), newKey.c_str());
					switch (_reply.type()) {
						case reply_type::STATUS:
							return _reply->str;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				bool del(const kerbal::utility::string_ref & key0)
				{
					static query _query("del %s");
					reply _reply = _query.execute(conn, key0.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				bool del(const kerbal::utility::string_ref & key0, const kerbal::utility::string_ref & key1)
				{
					static query _query("del %s %s");
					reply _reply = _query.execute(conn, key0.c_str(), key1.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				bool del(const kerbal::utility::string_ref & key0, const kerbal::utility::string_ref & key1, const kerbal::utility::string_ref & key2)
				{
					static query _query("del %s %s %s");
					reply _reply = _query.execute(conn, key0.c_str(), key1.c_str(), key2.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<typename std::iterator_traits<InputIterator>::value_type>::value,
				long long>::type
				del(InputIterator begin, InputIterator end)
				{
					std::vector<std::string> argv;
					argv.push_back("del");
					while (begin != end) {
						argv.push_back(redis_cast_to_string(*begin));
						++begin;
					}
					reply _reply = conn.argv_execute(argv.begin(), argv.end());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), argv.begin(), argv.end());
					}
				}

#	if __cplusplus >= 201103L
				template <typename ... Args>
				typename kerbal::type_traits::enable_if<is_redis_key_list<Args...>::value, long long>::type
				del(const kerbal::utility::string_ref & key0, Args&& ... keys)
				{
					kerbal::utility::string_ref args[] = { "del", key0, keys... };
					reply _reply = conn.argv_execute(begin(args), end(args));
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), args);
					}
				}
#	endif

				bool exists(const kerbal::utility::string_ref & key0) const
				{
					static query _query("exists %s");
					reply _reply = _query.execute(conn, key0.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				long long exists(const kerbal::utility::string_ref & key0, const kerbal::utility::string_ref & key1) const
				{
					static query _query("exists %s %s");
					reply _reply = _query.execute(conn, key0.c_str(), key1.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				long long exists(const kerbal::utility::string_ref & key0, const kerbal::utility::string_ref & key1, const kerbal::utility::string_ref & key2) const
				{
					static query _query("exists %s %s %s");
					reply _reply = _query.execute(conn, key0.c_str(), key1.c_str(), key2.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<typename std::iterator_traits<InputIterator>::value_type>::value,
				long long>::type
				exists(InputIterator begin, InputIterator end)
				{
					std::vector<std::string> argv;
					argv.push_back("exists");
					while (begin != end) {
						argv.push_back(redis_cast_to_string(*begin));
						++begin;
					}
					reply _reply = conn.argv_execute(argv.begin(), argv.end());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), argv.begin(), argv.end());
					}
				}

#	if __cplusplus >= 201103L
				/**
				 * @brief Check how many objects exists.
				 * @param key0 the first object's key
				 * @param args the remaining objects' key
				 * @return Existed object number.
				 */
				template <typename ... Args>
				typename kerbal::type_traits::enable_if<is_redis_key_list<Args...>::value, long long>::type
				exists(const kerbal::utility::string_ref & key0, Args&& ... keys) const
				{
					kerbal::utility::string_ref args[] = { "exist", key0, keys... };
					reply _reply = conn.argv_execute(begin(args), end(args));
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), args);
					}
				}
#	endif

				long long pexpire(const kerbal::utility::string_ref & key, long long milliseconds)
				{
					static query _query("pexpire %s %lld");
					reply _reply = _query.execute(conn, key.c_str(), milliseconds);
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				long long expire(const kerbal::utility::string_ref & key, long long seconds)
				{
					static query _query("expire %s %lld");
					reply _reply = _query.execute(conn, key.c_str(), seconds);
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				long long pexpire(const kerbal::utility::string_ref & key, const ::timeval & val)
				{
					return pexpire(key, val.tv_sec * 1000 + val.tv_usec / 1000);
				}

				long long expire(const kerbal::utility::string_ref & key, const ::timeval & val)
				{
					return expire(key, val.tv_sec);
				}

#	if __cplusplus >= 201103L
				long long pexpire(const kerbal::utility::string_ref & key, const std::chrono::milliseconds & millsec)
				{
					return pexpire(key, millsec.count());
				}

				long long expire(const kerbal::utility::string_ref & key, const std::chrono::seconds & sec)
				{
					return expire(key, sec.count());
				}
#	endif

				/**
				 * @brief Remove the expiration from a key.
				 */
				long long persist(const kerbal::utility::string_ref & key)
				{
					static query _query("persist %s");
					reply _reply = _query.execute(conn, key.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				long long pttl(const kerbal::utility::string_ref & key) const
				{
					static query _query("pttl %s");
					reply _reply = _query.execute(conn, key.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				long long ttl(const kerbal::utility::string_ref & key) const
				{
					static query _query("ttl %s");
					reply _reply = _query.execute(conn, key.c_str());
					switch (_reply.type()) {
						case reply_type::INTEGER:
							return _reply->integer;
						default:
							throw unexpected_case_exception(_reply.type(), _query.str());
					}
				}

				template <typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<typename std::iterator_traits<InputIterator>::value_type>::value,
				std::vector<kerbal::data_struct::optional<std::string> > >::type
				mget(InputIterator begin, InputIterator end) const
				{
					return this->mget<std::vector<kerbal::data_struct::optional<std::string> > >(begin, end);
				}

				template <typename ReturnType, typename InputIterator>
				typename kerbal::type_traits::enable_if<
						kerbal::redis_v2::is_redis_key_type<typename std::iterator_traits<InputIterator>::value_type>::value,
				ReturnType>::type
				mget(InputIterator begin, InputIterator end) const
				{
					std::vector<std::string> argv;
					argv.push_back("mget");
					while (begin != end) {
						argv.push_back(redis_cast_to_string(*begin));
						++begin;
					}
					reply _reply = conn.argv_execute(argv.begin(), argv.end());
					switch (_reply.type()) {
						case reply_type::ARRAY: {
							ReturnType res;
							reserve_if_could(res, _reply->elements);
							for (size_t i = 0; i < _reply->elements; ++i) {
								switch ((reply_type)(_reply->element[i]->type)) {
									case reply_type::STRING:
										res.push_back(_reply->element[i]->str);
										break;
									case reply_type::NIL:
										res.emplace_back();
										break;
									default:
										throw unexpected_case_exception(_reply.type(), argv.begin(), argv.end());
								}
							}
							return res;
						}
						default:
							throw unexpected_case_exception(_reply.type(), argv.begin(), argv.end());
					}
				}


#		if __cplusplus >= 201103L
				template <typename ... Args>
				typename kerbal::type_traits::enable_if<
					is_redis_key_list<Args...>::value,
				std::vector<kerbal::data_struct::optional<std::string>>>::type
				mget(const kerbal::utility::string_ref & key0, Args&& ... keys) const
				{
					return mget<std::vector<kerbal::data_struct::optional<std::string>>>(key0, std::forward<Args>(keys)...);
				}

				template <typename ReturnType, typename ... Args>
				typename kerbal::type_traits::enable_if<
					is_redis_key_list<Args...>::value,
				ReturnType>::type
				mget(const kerbal::utility::string_ref & key0, Args&& ... keys) const
				{
					kerbal::utility::string_ref args[] = { "mget", key0, keys... };
					reply _reply = conn.argv_execute(begin(args), end(args));
					switch (_reply.type()) {
						case reply_type::ARRAY: {
							ReturnType res;
							reserve_if_could(res, _reply->elements);
							for (size_t i = 0; i < _reply->elements; ++i) {
								switch ((reply_type)(_reply->element[i]->type)) {
									case reply_type::STRING:
										res.push_back(_reply->element[i]->str);
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
				mget_tuple(const kerbal::utility::string_ref & key0, Args&& ... keys)
				{
					kerbal::utility::string_ref args[] = { "mget", key0, keys... };
					reply _reply = conn.argv_execute(begin(args), end(args));
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

#		endif

		};


	} /* namespace redis_v2 */

} /* namespace kerbal */




#endif /* INCLUDE_KERBAL_REDIS_V2_OPERATION_HPP_ */
