/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:22:21 by hait-sal          #+#    #+#             */
/*   Updated: 2024/11/24 17:01:14 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

int main() {
    // if (ac == 2) {
        try {
            std::vector<int> nbrs;

            nbrs.push_back(42);
            nbrs.push_back(7);

            nbrs.push_back(19);
            nbrs.push_back(3);

            nbrs.push_back(56);
            nbrs.push_back(23);

            nbrs.push_back(8);
            nbrs.push_back(15);

            nbrs.push_back(17);
            nbrs.push_back(1);

            nbrs.push_back(12);
            nbrs.push_back(9);

            nbrs.push_back(99);
            nbrs.push_back(58);

            nbrs.push_back(33);
            std::cout << "Before : ";
            PmergeMe::print_vec(nbrs);
            PmergeMe::simpleSort(nbrs, 2);
            // std::cout << "<----------Final Result---------->" << std::endl;
            std::cout << "After : ";
            PmergeMe::print_vec(nbrs);
            // std::cout << "<----------Done---------->" << std::endl;
        }
        catch (std::exception &e) {
            std::cerr << "Error" <<std::endl;
        }
    // }
}

/* [ 42, 7, 19, 3, 56, 23, 8, 15, 17, 1, 12, 9, 99, 58, 33 ]
 {7 42} {3 19} {23 56} {8 15} {1 17} {9 12} {58 99} 33
 {3 19 7 42} {8 15 23 56} {9 12 1 17} 58 99 33
 3 19 7 42 8 15 23 56 9 12 1 17 58 99 33
*/




















// void swap_elements(std::vector<int>& toSort, int& start, int& pairSize) {
//     std::vector<int>::iterator it_start = toSort.begin() + start;
//     std::vector<int>::iterator it_end = toSort.begin() + (pairSize / 2);
//     for ( ; it_start != it_end; ++it_start) {
//         std::cout << start << " ********* " << std::endl;
//         int tmp = *it_start;
//         *it_start = *(it_start + pairSize / 2);
//         *(it_start + pairSize / 2) = tmp;
//     }
// }

// void swap_elements(std::vector<int>& toSort, int start, int& pairSize) {
//         std::cout << " ********* swaaaap " << std::endl;
//     std::vector<int>::iterator it_start = toSort.begin() + start;
//     int end = start + (pairSize / 2);
//     for (; start != end; ++start) {
//         std::cout << start << " - ********* " <<  *(it_start + start) << std::endl;
//         int tmp = *(it_start + start);
//         *(it_start + start) = *(it_start + start + pairSize / 2);
//         *(it_start + start + pairSize / 2) = tmp;
//         std::cout << "after : 1st -> " << *(it_start + start) << std::endl;
//         std::cout << "after : 2nd -> " << *(it_start + start + pairSize / 2) << std::endl;
//     }
// }

// void sortPairs(std::vector<int>& toSort, int& pairSize) {
//     int start = 0;
//     std::cout << "sortPairs --> " << pairSize << std::endl;
//     unsigned long end = start + pairSize - 1;
//     for (;  end < toSort.size(); ) {
//         std::cout << " +++++++++++ " << std::endl;
//         std::cout << "(" << start << ") comp1 -> " << toSort[start] << std::endl;
//         std::cout << "(" << start + pairSize / 2 << ") comp2 -> " << toSort[start + pairSize / 2] << std::endl;
//         if (toSort[start] > toSort[start + pairSize / 2])
//             swap_elements(toSort, start, pairSize);
//         start += pairSize;
//         end += pairSize;
//     }
//     std::cout << start << " ********* " << end << std::endl;
// }
