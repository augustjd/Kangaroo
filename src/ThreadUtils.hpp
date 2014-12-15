#ifndef __THREADUTILS_H__
#define __THREADUTILS_H__

#include <functional>
#include <algorithm>
#include <thread>
#include <vector>

#include <iostream>

using std::cout;
using std::endl;

using std::vector;

template <typename T>
void process_chunks(vector<T>& v, std::function<void(T&)> fn, unsigned int threads) {
    vector<std::thread> thread_pool;

    size_t chunk_size = v.size() / threads;
    for (unsigned int i = 0; i < threads; i++) {
        typename vector<T>::const_iterator l = v.begin() + (chunk_size * i);
        typename vector<T>::const_iterator r = l + chunk_size;

        if (i == threads - 1) {
            r = v.end();
        }
        cerr << "Thread " << i << " runs from " << *l << " to " << *(r - 1) << endl;

        thread_pool.push_back(std::thread([&] () { std::for_each(l, r, fn); }));
    }

    for (auto& thread : thread_pool) {
        thread.join();
    }
}

template <typename T>
void process_chunks(const vector<T>& v, std::function<void(const T&)> fn) {
    process_chunks(v,fn,std::thread::hardware_concurrency());
}

#endif /* end of include guard: __THREADUTILS_H__ */
