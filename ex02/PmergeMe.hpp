#include <vector>
#include <list>
#include <algorithm>
#include <sys/time.h>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <climits>

enum Type {VECTOR,LIST};

class PmergeMe
{
    private:
        std::vector<int> nums;
        std::list<std::pair<int, int> > pairsLst;
        std::vector<std::pair<int, int> > pairsVec;
        bool isOdd;
        int single;
        static void merge_sort(std::list<std::pair<int,int> >& pairs);
        static void merge_sort(std::vector<std::pair<int,int> >& pairs);
        static void insertion(std::vector<std::pair<int,int> >& pairs);
        static void insertion(std::list<std::pair<int,int> >& pairs);

    public:
        PmergeMe();
        PmergeMe(std::vector<int> &nums);
        PmergeMe(const PmergeMe& merge);
        PmergeMe& operator=(const PmergeMe& merge);
        ~PmergeMe();
        void init_pairs(Type type);
        double algorithm(Type type);
        void print_sorted_numbers(Type type);
        void print_unsorted_numbers();
};