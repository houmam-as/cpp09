/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:15:24 by hait-sal          #+#    #+#             */
/*   Updated: 2024/11/24 19:34:08 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::print_vec(vi& toSort) {
    vi::iterator it = toSort.begin();
    std::cout << "[ ";
    for (; it != toSort.end(); ++it) {
        if (it + 1 != toSort.end())
            std::cout << *it << ", ";
        else
            std::cout << *it << " ]" << std::endl;
    }
}

void print_vvi(vvi& vect) {
    vvi::iterator it = vect.begin();
    // std::cout << "******* vvi start *******" << std::endl;
    for (; it != vect.end(); ++it) {
        PmergeMe::print_vec(*it);
        std::cout << "____________________________" << std::endl;
    }
    // std::cout << "******* vvi end *******" << std::endl;
}

void print_vp(vp& pend) {
    vp::iterator it = pend.begin();
    for (; it != pend.end(); ++it) {
        PmergeMe::print_vec((*it).first);
        std::cout << "---------------------------" << std::endl;
    }
}

void swapParts(vi& toSort, int start, int& pairSize) {
    int end = start + pairSize / 2;
    for ( ; start != end; ++start) {
        int tmp = toSort[start];
        toSort[start] = toSort[start + pairSize / 2];
        toSort[start + pairSize / 2] = tmp;
    }
}

void sortPairs(vi& toSort, int pairSize) {
    int start = 0;
    unsigned long end = start + pairSize - 1;
    const int elSize = pairSize / 2;
    for ( ; end < toSort.size(); ) {
        if (toSort[start + elSize - 1] > toSort[start + pairSize - 1])
            swapParts(toSort, start, pairSize);
        start += pairSize;
        end = start + pairSize - 1;
    }
}

vvi makeChain(vi& toSort, int elSize) {
    int start = 0;
    unsigned long end = start + elSize - 1;
    vvi chain;
    int cnt = 0;
    int ndx = 0;
    vi tmp;
    for (; end < toSort.size(); ++ndx) {
        if (cnt == elSize) {
            start += elSize;
            end = start + elSize - 1;
            cnt = 0;
            chain.push_back(tmp);
            tmp.clear();
        }
        tmp.push_back(toSort[ndx]);
        ++cnt;
    }
    return chain;
}

void saveRemaining(vi& toSort, vi& remaining, int elSize) {
    vi::iterator it = toSort.begin() + toSort.size() - toSort.size() % elSize;
    for (; it != toSort.end(); ++it)
        remaining.push_back(*it);
}

vi vecToNbr(vvi& chain) {
    vvi::iterator it = chain.begin();
    vi ndx;
    for (; it != chain.end(); ++it) {
        ndx.push_back((*it)[it->size() - 1]);
    }
    return ndx;
}

bool compare(const vi& vec1, const vi& vec2) {
    return vec1.back() < vec2.back();
}

void insertPend(vvi& mainChain, vvi& pend) {
    vi ndxMain = vecToNbr(mainChain);
    vi ndxPend = vecToNbr(pend);
    vi::iterator it_pend = ndxPend.begin();
    for (int i = 0; it_pend != ndxPend.end(); ++it_pend) {
        // vi::iterator it = std::lower_bound(ndxMain.begin(), ndxMain.end(), *it_pend, compare);
        vi::iterator it = std::lower_bound(ndxMain.begin(), ndxMain.end(), *it_pend);
        int pos = it - ndxMain.begin();
        ndxMain.insert(it, *it_pend);
        int ndxPnd = it_pend - ndxPend.begin();
        mainChain.insert(mainChain.begin() + pos, pend[ndxPnd]);
        ++i;
    }
}

void increment_iterators(vvi& mainChain, int start, vp& pend) {
    vp::iterator it_pend = pend.begin() + start;
    for (; it_pend != pend.end(); ++it_pend) {
        if (it_pend->second != mainChain.end())
            std::advance(it_pend->second, 1);
    }
}

void insertPend(vvi& mainChain, vp& pend) {
    vp::iterator it_pend = pend.begin();
    for (; it_pend != pend.end(); ++it_pend) {
        std::cout << "Zfffffffffffffffffffffffffffffffffffffft" << std::endl;
        std::cout << it_pend->second - mainChain.begin()<< " || --> " << std::endl;
        vvi::iterator it = std::lower_bound(mainChain.begin(), it_pend->second, it_pend->first, compare);
        std::cout << "zzzzzzzffffffffffffffffffffffffffffffffffft" << std::endl;
        mainChain.insert(it, it_pend->first);
        int start = it_pend - pend.begin();
        increment_iterators(mainChain, start, pend);
    }
}

void vecElToVec(vi& dst, vi& src) {
    vi::iterator it = src.begin();
    for (; it != src.end(); ++it)
        dst.push_back(*it);
}

void rebornToSort(vi& toSort, vvi& mainChain, vi& remaining, bool& rest) {
    toSort.clear();
    vvi::iterator it = mainChain.begin();
    for (; it != mainChain.end(); ++it)
        vecElToVec(toSort, *it);
    if (rest)
        vecElToVec(toSort, remaining);
}

void separateChain(vvi& chain, vvi& mainChain, vvi& pend) {
    vvi::iterator it_chain = chain.begin();
    for (int i = 0; it_chain != chain.end(); ++it_chain) {
        if (i == 0 || i % 2 != 0)
            mainChain.push_back(*it_chain);
        else
            pend.push_back(*it_chain);
        ++i;
    }
}

void large_pend(unsigned long chainSize, vvi& mainChain, vvi& tmp_pend, vp& pend) {
    vvi::iterator it_main = mainChain.begin() + 2;
    vvi::iterator it_pend = tmp_pend.begin();

    for (; it_main != mainChain.end(); ) {
        pend.push_back(std::make_pair(*it_pend, it_main));
        ++it_main;
        ++it_pend;
    }
    if (it_main == mainChain.end() && chainSize % 2 != 0)
        pend.push_back(std::make_pair(*it_pend, it_main));
}

void elInsert(vi& toSort, int elSize) {
    vvi chain = makeChain(toSort, elSize);
    vi remaining;
    bool rest = false;
    if (toSort.size() % elSize != 0) {
        rest = true;
        saveRemaining(toSort, remaining, elSize);
    }
    vvi mainChain;
    vvi tmp_pend;
    separateChain(chain, mainChain, tmp_pend);
    std::cout << "<<<<<<<<<<<<<<<<<<<< main Chain >>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    print_vvi(mainChain);
    std::cout << "<<<<<<<<<<<<<<<<<<<< tmp Pend >>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    print_vvi(tmp_pend);
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<->>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

    vp pend;
    if (chain.size() > 3) { //insertion for a chain which is more than 3
        large_pend(chain.size(), mainChain, tmp_pend, pend);
        insertPend(mainChain, pend);
        std::cout << "Zfffffffffffffffffffffffffffffffffffffft" << std::endl;
        std::cout << "<<<<<<<<<<<<<<<<<<<< vp Pend >>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        print_vp(pend);
        std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<->>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    }
    else //insertion for a chain which is less than 4
    {
        std::cout << "Shiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiit" << std::endl;
        insertPend(mainChain, tmp_pend);
    }
    rebornToSort(toSort, mainChain, remaining, rest);
}

void PmergeMe::simpleSort(vi& toSort, int pairSize) {
        // std::cout << "forward --> " << pairSize << std::endl;
        sortPairs(toSort, pairSize);
        pairSize *= 2;
        if (toSort.size() / pairSize >= 1)
            simpleSort(toSort, pairSize);
        std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
        PmergeMe::print_vec(toSort);
        std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
        pairSize /= 2;
        const int elSize = pairSize / 2;
        if (toSort.size() / elSize == 2)
            return;

        // std::cout << "coming back <-- " << pairSize << std::endl;
        elInsert(toSort, elSize);
        PmergeMe::print_vec(toSort);
}
