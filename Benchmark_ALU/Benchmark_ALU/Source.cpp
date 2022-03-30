#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cmath>
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <chrono>

#include <stdio.h>
#ifdef _WIN32
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif
#include <time.h>

using namespace std;


class timer
{
public:
	timer() = default;
	void start_timing(const char* name_)
	{
		name = name_;
		begin = chrono::high_resolution_clock::now();
	}
	void stop_timing()
	{
		auto end = chrono::high_resolution_clock::now();
		auto dur = end - begin;
		auto ms = chrono::duration_cast<chrono::milliseconds>(dur).count();
		cout << setw(19) << name << ":" << setw(5) << ms << "ms" << endl;
	}

private:
	string name;
	chrono::high_resolution_clock::time_point begin;
};


template <typename Type>
void my_test(const char* name) {
    Type v = 0;
    // Do not use constants or repeating values
    //  to avoid loop unroll optimizations.
    // All values >0 to avoid division by 0
    // Perform ten ops/iteration to reduce
    //  impact of ++i below on measurements
    Type v0 = (Type)(rand() % 256) / 16 + 1;
    Type v1 = (Type)(rand() % 256) / 16 + 1;
    Type v2 = (Type)(rand() % 256) / 16 + 1;
    Type v3 = (Type)(rand() % 256) / 16 + 1;
    Type v4 = (Type)(rand() % 256) / 16 + 1;
    Type v5 = (Type)(rand() % 256) / 16 + 1;
    Type v6 = (Type)(rand() % 256) / 16 + 1;
    Type v7 = (Type)(rand() % 256) / 16 + 1;
    Type v8 = (Type)(rand() % 256) / 16 + 1;
    Type v9 = (Type)(rand() % 256) / 16 + 1;

    timer stopwatch;
    stopwatch.start_timing(name);

    //double t1 = mygettime();
    for (size_t i = 0; i < 1000000000; ++i) {
        v += v0;
        v -= v1;
        v += v2;
        v -= v3;
        v += v4;
        v -= v5;
        v += v6;
        v -= v7;
        v += v8;
        v -= v9;
    }
    // Pretend we make use of v so compiler doesn't optimize out
    //  the loop completely
    /*printf("%s add/sub: %f [%d]\n", name, mygettime() - t1, (int)v & 1);
    t1 = mygettime();*/
    stopwatch.stop_timing();

    stopwatch.start_timing(name);
    for (size_t i = 0; i < 1000000000; ++i) {
        v /= v0;
        v *= v1;
        v /= v2;
        v *= v3;
        v /= v4;
        v *= v5;
        v /= v6;
        v *= v7;
        v /= v8;
        v *= v9;
    }
    // Pretend we make use of v so compiler doesn't optimize out
    //  the loop completely
    //printf("%s mul/div: %f [%d]\n", name, mygettime() - t1, (int)v & 1);
    stopwatch.stop_timing();
}


void my_test2(const char* name) {
    timer stopwatch;
    stopwatch.start_timing(name);
    int aux = 0;

    int v0 = (int)(rand() % 256) / 16 + 1;
    int v1 = (int)(rand() % 256) / 16 + 1;
    int v2 = (int)(rand() % 256) / 16 + 1;
    int v3 = (int)(rand() % 256) / 16 + 1;
    int v4 = (int)(rand() % 256) / 16 + 1;
    int v5 = (int)(rand() % 256) / 16 + 1;
    int v6 = (int)(rand() % 256) / 16 + 1;
    int v7 = (int)(rand() % 256) / 16 + 1;
    int v8 = (int)(rand() % 256) / 16 + 1;
    int v9 = (int)(rand() % 256) / 16 + 1;

    for (size_t i = 0; i < 100000000000; i++) {
        aux = v0 ^ v1;
        aux = v1 ^ v2;
        aux = v2 ^ v3;
        aux = v3 ^ v4;
        aux = v4 ^ v5;
        aux = v5 ^ v6;
        aux = v6 ^ v7;
        aux = v7 ^ v8;
        aux = v8 ^ v9;
        aux = v9 ^ v0;
    }

    stopwatch.stop_timing();
}


int main() {
    /*my_test< short >("short");
    my_test< int >("int");
    my_test< long >("long");
    my_test< long long >("long long");*/
    //my_test< float >("float");
    //my_test< double >("double");

    my_test2("bool");

    return 0;
}