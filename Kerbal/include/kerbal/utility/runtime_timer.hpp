#ifndef RUNTIME_TIMER_HPP_
#define RUNTIME_TIMER_HPP_

//本文件继承自 exe_serve.hpp, 原文件现已拆分为若干文件

#include <iostream>
#include <string>
#include <kerbal/compatibility/tick_count.h>
#include <kerbal/utility/delete_cpy_and_assign.hpp>

class runtime_timer: virtual public kerbal::utility::Delete_cpy_and_assign<runtime_timer>
{
	protected:
		const unsigned long start_time;
		bool enable_show, have_shown;

		runtime_timer() :
				start_time(GetTickCount()), enable_show(false), have_shown(false)
		{
		}

		~runtime_timer()
		{
			if (this->enable_show) {
				unsigned long time_cost = GetTickCount() - start_time;
				std::cout << std::endl << "-------------------------------------" << std::endl;
				std::cout << "finished (took " << time_cost << " ms)" << std::endl;
			}
		}

	private:
		static runtime_timer p;

	public:

		static void enable(const std::string & program_name, const std::string & version = "")
		{
			if (!p.have_shown) {
				std::cout << program_name;
				std::cout << " [ ";
				if (version != "") {
					std::cout << "version " << version;
					std::cout << " , ";
				}
				std::cout << __DATE__ " , " __TIME__ " ]";
				std::cout << std::endl;
				p.have_shown = true;
				p.enable_show = true;
			}
		}

		static unsigned long show_time_cost()
		{
			unsigned long time_cost = GetTickCount() - p.start_time;
			std::cout << std::endl << "took " << time_cost << " ms" << std::endl;
			return time_cost;
		}
};

extern runtime_timer runtime_timer::p;

#endif	/* End RUNTIME_TIMER_HPP_ */
