#include "PmergeMe.hpp"


PmergeMe::PmergeMe():isOdd(false),single(0)
{

}

PmergeMe::PmergeMe(std::vector<int>& nums):nums(nums),isOdd(false),single(0)
{

}

PmergeMe::PmergeMe(const PmergeMe& merge):nums(merge.nums),pairsLst(merge.pairsLst),pairsVec(merge.pairsVec),isOdd(merge.isOdd),single(merge.single)
{

}

PmergeMe& PmergeMe::operator=(const PmergeMe& merge)
{
    if (this != &merge)
    {
        this->nums = merge.nums;
        this->pairsVec = merge.pairsVec;
        this->pairsLst = merge.pairsLst;
        this->isOdd = merge.isOdd;
        this->single = merge.single;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{

}

void PmergeMe::init_pairs(Type type)
{
    if (type == VECTOR)
        pairsVec.reserve((nums.size() / 2) + 1);
    for (size_t i = 0; i < nums.size();)
    {
        if (i + 1 < nums.size())
        {
            std::pair<int, int> p;
            if (nums[i] > nums[i + 1])
            {
                p.first = nums[i];
                p.second = nums[i + 1];
            }
            else
            {
                p.first = nums[i + 1];
                p.second = nums[i];
            }
            if (type == VECTOR)
                pairsVec.push_back(p);
            else
                pairsLst.push_back(p);
        }
        else
        {
            isOdd = true;
            single = nums[i];
        }
        i += 2;
    }
}


void PmergeMe::merge_sort(std::list<std::pair<int,int> >& pairs)
{
    if(pairs.size() <= 1)
        return;
    
    std::list<std::pair<int,int> >::iterator mid = pairs.begin();
    advance(mid,pairs.size()/2);
    std::list<std::pair<int,int> > left , right;
    left.splice(left.begin(),pairs,pairs.begin(),mid);
    right.splice(right.begin(),pairs,pairs.begin(),pairs.end());

    merge_sort(left);
    merge_sort(right);

    std::list<std::pair<int,int> >::iterator it1 = left.begin();
    std::list<std::pair<int,int> >::iterator it2 = right.begin();

    while (it1 != left.end() && it2 != right.end())
    {
        if (it1->first < it2->first)
        {
            pairs.splice(pairs.end(),left,it1++);
        }
        else
        {
            pairs.splice(pairs.end(),right,it2++);
        }
    }
    pairs.splice(pairs.end(),left);
    pairs.splice(pairs.end(),right);
}

void PmergeMe::merge_sort(std::vector<std::pair<int,int> >& pairs)
{
    if (pairs.size() <= 1)
        return;
    size_t mid = pairs.size() / 2;
    std::vector<std::pair<int,int> > left(pairs.begin(),pairs.begin() + mid);
    std::vector<std::pair<int,int> > right(pairs.begin() + mid,pairs.end());
    merge_sort(left);
    merge_sort(right);
    size_t left_len = left.size();
    size_t right_len = right.size();
    size_t l = 0,r = 0,index = 0;
    while (l < left_len && r < right_len)
    {
        if (left[l].first < right[r].first)
        {
            pairs[index++] = left[l++];
        }
        else
        {
            pairs[index++] = right[r++];
        }
    }
    while (l < left_len)
    {
        pairs[index++] = left[l++];
    }
    while (r < right_len)
    {
        pairs[index++] = right[r++];
    }
}


static void jacobstalNums(std::vector<size_t>& jacobstal)
{
    jacobstal.reserve(20);
    jacobstal[0] = 0;
    jacobstal[1] = 1;
    for (size_t i = 2; i < 20; i++)
    {
        jacobstal[i] = jacobstal[i - 1] + (jacobstal[i - 2] * 2);
    }
}

static bool compare(const std::pair<int, int> &elem, const std::pair<int, int> &tmp_elem)
{
    return elem.first < tmp_elem.first;
}

void PmergeMe::insertion(std::list<std::pair<int,int> >& pairs)
{
    std::list<std::pair<int, int> > losers = pairs;
    std::vector<size_t> jacob;
    jacobstalNums(jacob);
    std::list<std::pair<int, int> >::iterator oldIterat, currIterat, target, insert_pos, index;
    size_t jacobIndex = 2, pos;
    std::pair<int, int> tmp;
    for (size_t total = 0; total < losers.size();)
    {
        if (jacobIndex == 2)
        {
            currIterat = losers.begin();
            tmp.first = currIterat->second;
            tmp.second = currIterat->first;
            pairs.push_front(tmp);
            total++;
        }
        else
        {
            pos = jacob[jacobIndex] - 1;
            oldIterat = currIterat;
            if (pos < losers.size())
            {
                currIterat = losers.begin();
                advance(currIterat, pos);
            }
            else
                currIterat = --losers.end();
            index = currIterat;
            while (index != oldIterat)
            {
                tmp.first = index->second;
                tmp.second = index->first;
                target = find(pairs.begin(), pairs.end(), *index);
                insert_pos = std::lower_bound(pairs.begin(), target, tmp, compare);
                pairs.insert(insert_pos, tmp);
                --index;
                ++total;
            }
        }
        ++jacobIndex;
    }
}

void PmergeMe::insertion(std::vector<std::pair<int,int> >& pairs)
{
    std::vector<std::pair<int, int> > losers;
    std::pair<int, int> tmp;

    losers = pairs;
    std::vector<size_t> jacob;
    jacobstalNums(jacob);
    size_t jIndex = 2, currIndex = 0, oldIndex = 0 ,total = 0;
    std::vector<std::pair<int, int> >::iterator target, insert_pos;
    while (total < losers.size())
    {
        if (jacob[jIndex] == 1)
        {
            tmp.first = losers[0].second;
            tmp.second = losers[0].first;
            pairs.insert(pairs.begin(),tmp);
            total++;
        }
        else
        {
            if (jacob[jIndex] < losers.size())
            {
                currIndex = jacob[jIndex] - 1;
            }
            else
                currIndex = losers.size() - 1;
            for (size_t i = currIndex; i > oldIndex; --i)
            {
                tmp.first = losers[i].second;
                tmp.second = losers[i].first;
                target = find(pairs.begin(),pairs.end(),losers[i]);
                insert_pos = std::lower_bound(pairs.begin(),target,tmp,compare);
                pairs.insert(insert_pos,tmp);
                total++;
            }
        }
        oldIndex = currIndex;
        jIndex++;
    }
}

double PmergeMe::algorithm(Type type)
{
    timeval t1, t2;
    gettimeofday(&t1, NULL);

    this->init_pairs(type);

    if (type == LIST)
        merge_sort(this->pairsLst);
    else
        merge_sort(this->pairsVec);

    if (type == LIST)
        insertion(this->pairsLst);
    else
        insertion(this->pairsVec);
    
    if (this->isOdd)
    {
        std::pair<int, int> tmp;
        tmp.first = this->single;
        tmp.second = this->single;
        if (type == VECTOR)
        {
            std::vector<std::pair<int, int> >::iterator insert_pos;
            insert_pos = std::lower_bound(pairsVec.begin(), pairsVec.end(), tmp, compare);
            pairsVec.insert(insert_pos, tmp);
        }
        else
        {
            std::list<std::pair<int, int> >::iterator insert_pos;
            insert_pos = std::lower_bound(pairsLst.begin(), pairsLst.end(), tmp, compare);
            pairsLst.insert(insert_pos, tmp);       
        }
    }

    gettimeofday(&t2, NULL);
    double time = ((t2.tv_sec - t1.tv_sec) * 1000000.0) + (t2.tv_usec - t1.tv_usec); 
    return time;
}

void PmergeMe::print_sorted_numbers(Type type)
{
    if (type == LIST)
    {
        std::list<std::pair<int,int> >::iterator it = this->pairsLst.begin();
        for (; it != this->pairsLst.end();++it)
        {
            std::cout << it->first << ' ';
        }
    }
    if (type == VECTOR)
    {
        for (size_t i = 0; i < this->pairsVec.size(); ++i)
        {
            std::cout << this->pairsVec[i].first << ' ';
        }
    }
    std::cout << std::endl;
}

void PmergeMe::print_unsorted_numbers()
{
    for (size_t i = 0; i < this->nums.size(); i++)
    {
        std::cout << this->nums[i] << ' ';
    }
    std::cout << std::endl;
}