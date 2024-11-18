/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:15:24 by hait-sal          #+#    #+#             */
/*   Updated: 2024/11/04 12:18:55 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::print_vec(std::vector<int>& toSort) {
    std::cout << "<---------- print vector start ---------->" << std::endl;
    std::vector<int>::iterator it = toSort.begin();
    std::cout << "vec = [ ";
    for (; it != toSort.end(); ++it)
        std::cout << *it << ", ";
    std::cout << " ]" << std::endl;
    std::cout << "<---------- print vector end ---------->" << std::endl;
}

// std::cout << "error" << std::endl;
void swapParts(std::vector<int>& toSort, int start, int& pairSize) {
    // std::cout << "------------------------< swapParts >-------------------------" << std::endl;
    int end = start + pairSize / 2;
    for ( ; start != end; ++start) {
        int tmp = toSort[start];
        toSort[start] = toSort[start + pairSize / 2];
        toSort[start + pairSize / 2] = tmp;
    }
    // std::cout << "------------------------< swapParts >-------------------------" << std::endl;
}

void sortPairs(std::vector<int>& toSort, int pairSize) {
    // std::cout << "------------------------< sort Pairs >-------------------------" << std::endl;
    int start = 0;
    unsigned long end = start + pairSize - 1;
    const int elSize = pairSize / 2;
    for ( ; end < toSort.size(); ) {
        if (toSort[start + elSize - 1] > toSort[start + pairSize - 1])
            swapParts(toSort, start, pairSize);
        start += pairSize;
        end = start + pairSize - 1;
    }
    // std::cout << "------------------------< sorted Pairs >-------------------------" << std::endl;
}

std::vector< std::vector<int> > makeChain(std::vector<int>& toSort, int elSize) {
    int start = 0;
    unsigned long end = start + elSize - 1;
    std::vector< std::vector<int> > chain;
    int cnt = 0;
    int ndx = 0;
    std::vector<int> tmp;
    for (; end < toSort.size(); ++ndx) {
        if (cnt == elSize) {
            start += elSize;
            end = start + elSize - 1;
            cnt = 0;
            chain.push_back(tmp);
            tmp.clear();
            // PmergeMe::print_vec(tmp);
        }
        tmp.push_back(toSort[ndx]);
        ++cnt;
    }
    return chain;
}

void saveRemaining(std::vector<int>& toSort, std::vector<int>& remaining, int elSize) {
    std::vector<int>::iterator it = toSort.begin() + toSort.size() - toSort.size() % elSize;
    std::cout << "idiot calcul --> " << toSort.size() % elSize << "||" << toSort.size() - toSort.size() % elSize << std::endl;
    for (; it != toSort.end(); ++it)
        remaining.push_back(*it);

    std::cout << "Start Remaining -> " <<  std::endl;
    PmergeMe::print_vec(remaining);
    std::cout << "End Remaining -> " <<  std::endl;
}

void separateChain(std::vector< std::vector<int> >& chain, std::vector< std::vector<int> >& mainChain, std::vector<std::vector<int> >& pend) {
    std::vector< std::vector<int> >::iterator it_chain = chain.begin();
    for (int i = 0; it_chain != chain.end(); ++it_chain) {
        if (i == 0 || i % 2 != 0)
            mainChain.push_back(*it_chain);
        else
            pend.push_back(*it_chain);
        ++i;
    }
}

std::vector<int> vecToNbr(std::vector< std::vector<int> >& chain) {
    std::vector< std::vector<int> >::iterator it = chain.begin();
    std::vector <int> ndx;
    for (; it != chain.end(); ++it) {
        ndx.push_back((*it)[it->size() - 1]);
    }
    return ndx;
}

void insertPend(std::vector< std::vector<int> >& mainChain, std::vector< std::vector<int> >& pend) {
    std::vector <int> ndxMain = vecToNbr(mainChain);
    std::vector <int> ndxPend = vecToNbr(pend);
    std::vector<int>::iterator it_pend = ndxPend.begin();
    for (int i = 0; it_pend != ndxPend.end(); ++it_pend) {
        std::vector<int>::iterator it = std::lower_bound(ndxMain.begin(), ndxMain.end(), *it_pend);
        int pos = it - ndxMain.begin();
        ndxMain.insert(it, *it_pend);
        int ndxPnd = it_pend - ndxPend.begin();
        mainChain.insert(mainChain.begin() + pos, pend[ndxPnd]);
        ++i;
    }
}

void vecElToVec(std::vector<int>& dst, std::vector<int>& src) {
    std::vector<int>::iterator it = src.begin();
    for (; it != src.end(); ++it)
        dst.push_back(*it);
}

void rebornToSort(std::vector<int>& toSort, std::vector< std::vector<int> >& mainChain, std::vector<int>& remaining, bool& rest) {
    std::cout << "__________________ Before adding mainChain __________________" << std::endl;
    PmergeMe::print_vec(toSort);
    std::cout << "__________________ Before adding mainChain __________________" << std::endl;
    toSort.clear();
    std::cout << "__________________ This the mainChain __________________" << std::endl;
    std::vector< std::vector<int> >::iterator main_it = mainChain.begin();
    for (; main_it != mainChain.end(); ++main_it)
        PmergeMe::print_vec(*main_it);
    std::cout << "__________________ This the mainChain __________________" << std::endl;
    std::vector< std::vector<int> >::iterator it = mainChain.begin();
    for (; it != mainChain.end(); ++it)
        vecElToVec(toSort, *it);
    std::cout << "__________________ After adding mainChain __________________" << std::endl;
    PmergeMe::print_vec(toSort);
    std::cout << "__________________ After adding mainChain __________________" << std::endl;
    if (rest) {
        vecElToVec(toSort, remaining);
        std::cout << "__________________ This the remaining __________________" << std::endl;
        PmergeMe::print_vec(remaining);
        std::cout << "__________________ This the remaining __________________" << std::endl;
        std::cout << "__________________ After adding remaining __________________" << std::endl;
        PmergeMe::print_vec(toSort);
        std::cout << "__________________ Remaining added __________________" << std::endl;
    }
}

void elInsert(std::vector<int>& toSort, int elSize) {
    std::vector< std::vector<int> > chain = makeChain(toSort, elSize);
    std::vector<int> remaining;
    bool rest = false;
    if (toSort.size() % elSize != 0) {
        rest = true;
        saveRemaining(toSort, remaining, elSize);
    }
    std::vector< std::vector<int> > mainChain;
    std::vector< std::vector<int> > pend;
    separateChain(chain, mainChain, pend);
    insertPend(mainChain, pend);
    // toSort.clear();
    rebornToSort(toSort, mainChain, remaining, rest);
}

void PmergeMe::simpleSort(std::vector<int>& toSort, int pairSize) {
        std::cout << "forward --> " << pairSize << std::endl;
        // print_vec(toSort);
        sortPairs(toSort, pairSize);
        // std::cout << "_______________ Vec before Sort Start _______________" << pairSize << std::endl;
        // print_vec(toSort);
        // std::cout << "_______________ Vec before Sort end _______________" << pairSize << std::endl;
        pairSize *= 2;
        if (toSort.size() / pairSize >= 1)
            simpleSort(toSort, pairSize);
        pairSize /= 2;
        const int elSize = pairSize / 2;
        if (toSort.size() / elSize == 2)
            return;
        std::cout << "coming back <-- " << pairSize << std::endl;
        elInsert(toSort, elSize);
        // std::cout << "--------------- End after elInsert---------------" << std::endl;
}
