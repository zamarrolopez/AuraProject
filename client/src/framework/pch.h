#pragma once

#include "framework/core/application.h"
// Información de copyright mantenida

// Versión mínima de Windows requerida
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00 // Windows 10
#endif

#ifndef NTDDI_VERSION
#define NTDDI_VERSION NTDDI_WIN10
#endif

#include <sdkddkver.h> // Necesario para validar versiones

// common C headers
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// common STL headers
#include <algorithm>
#include <array>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <typeinfo>
#include <unordered_map>
#include <vector>

// Bibliotecas externas
#include <parallel_hashmap/btree.h>
#include <parallel_hashmap/phmap.h>
#include <pugixml.hpp>

using namespace std::literals;
