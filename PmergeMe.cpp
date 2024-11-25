/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:15:24 by hait-sal          #+#    #+#             */
/*   Updated: 2024/11/25 14:48:07 by hait-sal         ###   ########.fr       */
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
    std::cout << "pppppppppppppppppppp Start qqqqqqqqqqqqqqqqqqqqqqq" << std::endl;
    vp::iterator it = pend.begin();
    for (; it != pend.end(); ++it) {
        PmergeMe::print_vec(it->first);
        std::cout << "------------- Second --------------" << std::endl;
        if (pend.size() % 2 != 0 && *it == pend[pend.size() - 1]) {
            std::cout << "end reached !!!" << std::endl;
            PmergeMe::print_vec(*(it->second));
        }
        else
            PmergeMe::print_vec(*(it->second));
        std::cout << "------------- Pair Printed --------------" << std::endl;
    }
    std::cout << "pppppppppppppppppppp End qqqqqqqqqqqqqqqqqqqqqqq" << std::endl;

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


//edited in my github workspace
// bool operator<(const vi& vec1, const vi& vec2) {
//     return vec1.back() < vec2.back();
// }

// bool compare(const vi& vec1, const vi& vec2) {
//     return vec1 < vec2;
// }


bool compare(const vi& vec1, const vi& vec2) {
    return vec1.back() < vec2.back();
}

void insertPend(vvi& mainChain, vvi& pend) {
    vi ndxMain = vecToNbr(mainChain);
    vi ndxPend = vecToNbr(pend);
    vi::iterator it_pend = ndxPend.begin();
    for (int i = 0; it_pend != ndxPend.end(); ++it_pend) {
        vi::iterator it = std::lower_bound(ndxMain.begin(), ndxMain.end(), *it_pend, compare);
        int pos = it - ndxMain.begin();
        ndxMain.insert(it, *it_pend);
        int ndxPnd = it_pend - ndxPend.begin();
        mainChain.insert(mainChain.begin() + pos, pend[ndxPnd]);
        ++i;
    }
}

void increment_iterators(vvi& mainChain, vp& pend, size_t incr_nbr) {
    vp::iterator it_pend = pend.begin();
    for (; it_pend != pend.end(); ++it_pend) {
        if (it_pend->second != mainChain.end()) {
            PmergeMe::print_vec(*(it_pend->second));
            std::advance(it_pend->second, incr_nbr);
        }
    }
}

vi jacobsthal_diff() {
    vi jacobDiff;

    unsigned long initialNumbers[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765, 2863311531, 5726623061, 11453246123, 22906492245, 45812984491, 91625968981, 183251937963};
    for (size_t    i = 0; i < 30; i++)
        jacobDiff.push_back(initialNumbers[i + 1] - initialNumbers[i]);
    return (jacobDiff);
}

void insertPend(vvi& mainChain, vp& pend) {
    vi jacobi = jacobsthal_diff();
    vi::iterator it_jacobi = jacobi.begin();
    vp::iterator it_begin;
    for (; pend.size() != 0; ++it_jacobi) {
        if (it_jacobi != jacobi.end() && pend.size() >= (size_t)*it_jacobi)
            it_begin = pend.begin() + *it_jacobi - 1;
        else
            it_begin = pend.end() - 1;
        for (; it_begin >= pend.begin(); --it_begin) {
            vvi::iterator it = std::lower_bound(mainChain.begin(), it_begin->second, it_begin->first, compare);
            mainChain.insert(it, it_begin->first);
            pend.erase(it_begin);
        }
        increment_iterators(mainChain, pend, *it_jacobi);
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

void large_pend(vvi& mainChain, vvi& tmp_pend, vp& pend) {
    vvi::iterator it_main = mainChain.begin() + 2;
    vvi::iterator it_pend = tmp_pend.begin();

    for (; it_main != mainChain.end(); ) {
        pend.push_back(std::make_pair(*it_pend, it_main));
        ++it_main;
        ++it_pend;
    }
    if (tmp_pend.size() % 2 != 0 && mainChain.size() % 2 == 0)
        pend.push_back(std::make_pair(*it_pend, mainChain.end()));
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
    mainChain.reserve(chain.size() / elSize);
    vvi tmp_pend;
    separateChain(chain, mainChain, tmp_pend);
    std::cout << "<<<<<<<<<<<<<<<<<<<< main Chain >>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    print_vvi(mainChain);
    std::cout << "<<<<<<<<<<<<<<<<<<<< tmp Pend >>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    print_vvi(tmp_pend);
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<->>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;

    vp pend;
    if (chain.size() > 3) { //insertion for a chain which is more than 3
        large_pend(mainChain, tmp_pend, pend);
        std::cout << "Zfffffffffffffffffffffffffffffffffffffft" << std::endl;
        std::cout << "<<<<<<<<<<<<<<<<<<<< vp Pend >>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        print_vp(pend);
        std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<->>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        insertPend(mainChain, pend);
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
        elInsert(toSort, elSize);
        PmergeMe::print_vec(toSort);
}
