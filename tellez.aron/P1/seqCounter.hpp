#ifndef SEQCOUNTER_HPP
#define SEQCOUNTER_HPP
#include <stdexcept>

namespace tellez
{
  class LongestDecreasingCounter {
  public:
    LongestDecreasingCounter();
    void processValue(int value);
    size_t getLongestSequenceLength() const;
  private:
    int current_seq_count;
    int max_seq_count;
    int actual;
  };
}
#endif
