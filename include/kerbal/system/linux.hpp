/*
 * linux.hpp
 *
 *  Created on: 2018年6月10日
 *      Author: peter
 */

#ifndef KERBAL_INCLUDE_KERBAL_SYSTEM_LINUX_HPP_
#define KERBAL_INCLUDE_KERBAL_SYSTEM_LINUX_HPP_

#ifdef __linux
#	include <string>
#	include <list>

#	include <unistd.h>
#	include <netdb.h>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#	include <pwd.h>

inline std::string get_user_name()
{
	return std::string(getpwuid(getuid())->pw_name);
}

inline int get_processors_number()
{
	unsigned int count = 1;
	count = sysconf(_SC_NPROCESSORS_CONF);
	return count;
}

std::string get_host_name()
{
	char hname[128];
    gethostname(hname, sizeof(hname));
    return hname;
}

std::list<std::string> get_addr_list(const char * hname)
{
    struct hostent *hent = gethostbyname(hname);

    //hent = gethostent();
    std::list<std::string> res;

    for(int i = 0; hent->h_addr_list[i]; ++i) {
        res.push_back(inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
    }
    return res;
}

std::list<std::string> get_addr_list(const std::string & hname)
{
    return get_addr_list(hname.c_str());
}

#endif

#endif /* KERBAL_INCLUDE_KERBAL_SYSTEM_LINUX_HPP_ */
