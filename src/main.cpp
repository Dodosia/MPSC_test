#include "logger.hpp"

int main() {
  try {
#ifdef logger_with_test
    logger_with_test logger;
#else
    logger logger;
#endif
    std::list<std::jthread> threads;
    std::atomic_int threads_counter{1};
    std::generate_n(std::back_inserter(threads), 5u, [&] {
      return std::jthread{[&] {
        const auto thread_id = threads_counter.fetch_add(1);
        logger.post(std::format("[{}] one\n", thread_id));
        std::this_thread::sleep_for(1s);
        logger.post(std::format("[{}] two\n", thread_id));
      }};
    });
    const std::jthread logger_thread{[&](std::stop_token stop) {
      logger.run(stop);
    }};
    threads.clear();
    logger.post("[0] done\n");
  }
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
