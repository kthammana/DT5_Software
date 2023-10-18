/*
 * Debug.h
 *
 *  Created on: Mar 14, 2023
 *      Author: keert
 */

#ifndef SRC_DEBUG_H_
#define SRC_DEBUG_H_

#define DEBUG 1
#if DEBUG
	#define Debug(__info,...) printf("Debug: " __info,##__VA_ARGS__)
#else
	#define Debug(__info,...)
#endif

#endif /* SRC_DEBUG_H_ */
