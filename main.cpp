/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:22:21 by hait-sal          #+#    #+#             */
/*   Updated: 2024/11/25 15:41:20 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"

typedef std::string string;

int strtoi(const string& str) {
    std::istringstream iss(str);
    int result;
    iss >> result;
    if (iss.fail() || !iss.eof())
        throw std::invalid_argument("Invalid input: Cannot convert to integer");
    return result;
}

vi check_input(string input) {
    vi nbrs;
    string tmp;
    string::iterator it_input;
    for (; it_input != input.end(); ++it_input) {
        if (*it_input == ' ') {
            nbrs.push_back(strtoi(tmp));
            tmp.clear();
            continue;
        }
        tmp.push_back(*it_input);
    }
    return nbrs;
}

int main(int ac, char **av) {
    if (ac == 2) {
        try {
            check_input(av[1]);
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
            std::cout << "After : ";
            PmergeMe::print_vec(nbrs);
        }
        catch (std::exception &e) {
            std::cerr << "Error" <<std::endl;
        }
    }
}
