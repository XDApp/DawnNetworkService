// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string.h>
#include <time.h>

#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib")

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <cmath>
#include <vector>
// TODO: reference additional headers your program requires here

#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")