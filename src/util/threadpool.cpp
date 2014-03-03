#include <llmr/util/threadpool.hpp>

using namespace llmr::util;

Threadpool::Threadpool(Callback callback, int max_workers)
    : max_workers(max_workers),
      callback(callback) {
}

void Threadpool::add(void *data) {
    if (worker_count < max_workers) {
        workers.emplace_front(*this);
        worker_count++;
    }

    pthread_mutex_lock(&mutex);
    tasks.push(data);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&condition);
}

Threadpool::Worker::Worker(Threadpool& pool)
    : pool(pool) {
    pthread_create(&thread, nullptr, loop, (void *)this);
}

Threadpool::Worker::~Worker() {
    pthread_cancel(thread);
}


void *Threadpool::Worker::loop(void *ptr) {
    Worker *worker = static_cast<Worker *>(ptr);
    Threadpool& pool = worker->pool;

    pthread_setname_np("worker");
    pthread_mutex_lock(&pool.mutex);
    while (true) {
        if (pool.tasks.size()) {
            void *task = pool.tasks.front();
            pool.tasks.pop();
            pthread_mutex_unlock(&pool.mutex);
            pool.callback(task);
            pthread_mutex_lock(&pool.mutex);
        } else {
            pthread_cond_wait(&pool.condition, &pool.mutex);
        }
    }

    return nullptr;
}
