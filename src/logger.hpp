// =================================================================================================
// Benchmark
// =================================================================================================
// Threads: 16, Iterations: 1'600'000 (Total)
// CPU: Intel(R) Core(TM) i7-10750H (16 × 2592 MHz)
// CPU Caches:
//   L1 Data 32 KiB (x6)
//   L1 Instruction 32 KiB (x6)
//   L2 Unified 256 KiB (x6)
//   L3 Unified 12288 KiB (x1)
// -------------------------------------------------------------------------------------------------
// Windows                                        Time             CPU
// -------------------------------------------------------------------------------------------------
// dynamic<logger>                                536 ns          312 ns
// literal<logger>                                532 ns          273 ns

void print(std::string_view text);

class logger
{
public:
  logger()
  {
    // Создаем фиктивную голову односвязного списка.
    head = new node;
    head->next.store(nullptr, std::memory_order_relaxed);
    // Хвост изначально указывает на ту же фиктивную голову.
    tail.store(head, std::memory_order_relaxed);
  }

  ~logger()
  {
    // Перед уничтожением вычищаем все накопленные сообщения.
    drain();
    // Освобождаем всю цепочку.
    node* p = head;
    while (p != nullptr)
    {
      node* n = p->next.load(std::memory_order_relaxed);
      delete p;
      p = n;
    }
  }

  // Вызывается одновременно из множества потоков-производителей.
  void post(std::string_view text)
  {
    // Готовим новый узел списка.
    node* n = new node;
    n->text = std::string(text);
    n->next.store(nullptr, std::memory_order_relaxed);
    // Атомарно присваиваем этот узел хвосту очереди.
    node* old = tail.exchange(n, std::memory_order_acq_rel);
    // Связываем предыдущий хвост с новым узлом.
    old->next.store(n, std::memory_order_release);
    // Будим потребителя.
    tail.notify_one();
  }

    // Запускается в одном потребительском потоке.
  void run(std::stop_token stop) noexcept 
  {
    const std::stop_callback callback(stop, [this] { post(""); });
    for (;;)
    {
      // Выгружаем всё, что уже прислали производители.
      drain();
      if (stop.stop_requested())
        break;
      if (head->next.load(std::memory_order_relaxed) == nullptr)
      {
        // Если очередь пуста, снимаем наблюдаемое значение tail и ждем, пока оно изменится.
        node* seen = tail.load(std::memory_order_relaxed);
        // Повторная проверка перед сном.
        if (head->next.load(std::memory_order_relaxed) == nullptr)
          tail.wait(seen);
      }
    }
    // Финальная выгрузка перед выходом.
    drain();
  }

private:
  struct node
  {
    std::atomic<node*> next;
    std::string text;
  };

  node* head = nullptr; // Неатомарная голова - читает и двигает только потребитель. 
  alignas(64) std::atomic<node*> tail; // Атомарный хвост - на него пишут все производители.

  // Забирает все доступные элементы из очереди и печатает их.
  void drain()
  {
    for (node* n = head->next.load(std::memory_order_acquire); n != nullptr; n = head->next.load(std::memory_order_acquire)) {
      print(n->text);
      delete std::exchange(head, n);
    }
  }
};

#define logger logger
