//
// Created by peter on 2020/11/5.
//

#ifndef KERBAL_THREE_WAY_COMPARISON_HPP
#define KERBAL_THREE_WAY_COMPARISON_HPP

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/operators/less_than_comparable.hpp>
#include <kerbal/operators/equality_comparable.hpp>

//#include <compare>

//std::strong_ordering

namespace kerbal
{

	namespace compare
	{

		namespace detail
		{

			class order:
					public kerbal::operators::less_than_comparable<order>,
					public kerbal::operators::equality_comparable<order>
			{
				protected:
					typedef signed char result_type;
					result_type result;

				public:

#			if __cplusplus >= 201103L
					static constexpr result_type equal = 0;
					static constexpr result_type less = -1;
					static constexpr result_type greater = 1;
#			else
					static const result_type equal = 0;
					static const result_type less = -1;
					static const result_type greater = 1;
#			endif

					KERBAL_CONSTEXPR
					explicit order(result_type result) KERBAL_NOEXCEPT
						: result(result)
					{
					}

				public:
					KERBAL_CONSTEXPR
					friend
					bool operator==(const order & lhs, const order & rhs) KERBAL_NOEXCEPT
					{
						return lhs.result == rhs.result;
					}

					KERBAL_CONSTEXPR
					friend
					bool operator<(const order & lhs, const order & rhs) KERBAL_NOEXCEPT
					{
						return lhs.result < rhs.result;
					}

			};


//#	if __cplusplus >= 201103L
//		constexpr order::result_type order::equal;
//		constexpr order::result_type order::less;
//		constexpr order::result_type order::greater;
//#	else
//		const order::result_type order::equal;
//		const order::result_type order::less;
//		const order::result_type order::greater;
//#	endif

		} // namespace detail

		class strong_ordering:
				public kerbal::operators::less_than_comparable<strong_ordering>,
				public kerbal::operators::equality_comparable<strong_ordering>
		{
			protected:
				typedef detail::order result_type;
				detail::order result;

			public:

#			if __cplusplus >= 201103L
				static const strong_ordering equal;
				static const strong_ordering less;
				static const strong_ordering greater;
#			else
				static const strong_ordering equal;
				static const strong_ordering less;
				static const strong_ordering greater;
#			endif

			private:

				KERBAL_CONSTEXPR
				explicit strong_ordering(result_type result) KERBAL_NOEXCEPT
						: result(result)
				{
				}

				KERBAL_CONSTEXPR
				friend
				bool operator==(const strong_ordering & lhs, const strong_ordering & rhs) KERBAL_NOEXCEPT
				{
					return lhs.result == rhs.result;
				}

				KERBAL_CONSTEXPR
				friend
				bool operator<(const strong_ordering & lhs, const strong_ordering & rhs) KERBAL_NOEXCEPT
				{
					return lhs.result < rhs.result;
				}

		};

		KERBAL_CONSTEXPR const strong_ordering strong_ordering::equal = strong_ordering(detail::order(detail::order::equal));
		KERBAL_CONSTEXPR const strong_ordering strong_ordering::less = strong_ordering(detail::order(detail::order::less));
		KERBAL_CONSTEXPR const strong_ordering strong_ordering::greater = strong_ordering(detail::order(detail::order::greater));


		template <typename Tp>
		struct three_way_integral
		{

				KERBAL_CONSTEXPR
				strong_ordering operator()(const Tp & lhs, const Tp & rhs) KERBAL_NOEXCEPT
				{
					return lhs < rhs ? strong_ordering::less :
							rhs < lhs ? strong_ordering::greater :
										strong_ordering::equal;
				}
		};

	} // namespace compare

} // namespace kerbal

#endif //KERBAL_THREE_WAY_COMPARISON_HPP
