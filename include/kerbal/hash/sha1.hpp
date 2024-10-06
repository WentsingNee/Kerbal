/**
 * @file       sha1.hpp
 * @brief
 * @date       2019-8-11
 * @author     Peter Nee, Steve Reid
 * @copyright
 *
 *
 *  kerbal::hash::SHA1 refers the source code written by Steve Reid, of which
 *  you can find the original c-style source file from redis5.0/sha1.
 *  To use elegantly, the algorithm was transferred to C++-style and then
 *  optimized by Peter Nee of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *  of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/).
 *
 *  Here is the copyright of the original file. Though Steve didn't have any other argument
 *  about copyright in these files but I sincerely hope that you can retain the
 *  copyright notice in redistributions of source code. Thank you!

 	================ sha1.c ================
	SHA-1 in C
	By Steve Reid <steve@edmweb.com>
	100% Public Domain

	Test Vectors (from FIPS PUB 180-1)
	"abc"
	  A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
	"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
	  84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
	A million repetitions of "a"
	  34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F


	================ sha1.h ================
	SHA-1 in C
	By Steve Reid <steve@edmweb.com>
	100% Public Domain

 */

#ifndef KERBAL_HASH_SHA1_HPP
#define KERBAL_HASH_SHA1_HPP

#include <kerbal/hash/sha1/sha1.fwd.hpp>
#include <kerbal/hash/sha1/sha1.decl.hpp>
#include <kerbal/hash/sha1/sha1.impl.hpp>

#endif // KERBAL_HASH_SHA1_HPP
