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

void print_str(string toSort, string str = "0x1337") {
    string::iterator it = toSort.begin();
    std::cout << str;
    for (; it != toSort.end(); ++it) {
        if (it + 1 != toSort.end())
            std::cout << *it << ", ";
        else
            std::cout << *it << " ]" << std::endl;
    }
}

void print_vec(const vi& toSort, string str = "0x1337") {
    vi::const_iterator it = toSort.begin();
    std::cout << str;
    for (; it != toSort.end(); ++it) {
        if (it + 1 != toSort.end())
            std::cout << *it << " ";
        else
            std::cout << *it << std::endl;
    }
}

void print_deque(const di& toSort, string str = "0x1337") {
    di::const_iterator it = toSort.begin();
    std::cout << str;
    for (; it != toSort.end(); ++it) {
        if (it + 1 != toSort.end())
            std::cout << *it << " ";
        else
            std::cout << *it << std::endl;
    }
}

int strtoi(const string& str) {
    std::istringstream iss(str);
    int result;
    iss >> result;
    if (iss.fail() || !iss.eof())
        throw std::invalid_argument("Cannot convert to integer");
    return result;
}

void check_input(string str) {
    string::iterator it_str = str.begin();
    for (; it_str != str.end(); ++it_str) {
        if (*it_str == ' ' && (it_str + 1) != str.end() && *(it_str + 1) < 48 && *(it_str + 1) > 57)
            throw std::invalid_argument("Invalid number");
        if (*it_str < 48 && *it_str > 57 && *it_str != ' ')
            throw std::invalid_argument("Invalid number");
    }
}

std::pair<vi, di> get_input(string input) {
    vi vec;
    di deq;
    string tmp;
    string::iterator it_input = input.begin();
    for (; it_input != input.end(); ++it_input) {
        if (*it_input == ' ') {
            vec.push_back(strtoi(tmp));
            deq.push_back(strtoi(tmp));
            tmp.clear();
            continue;
        }
        tmp.push_back(*it_input);
    }
    if  (it_input == input.end()) {
        vec.push_back(strtoi(tmp));
        deq.push_back(strtoi(tmp));

    }
    return make_pair(vec, deq);
}

int main(int ac, char **av) {
    try {
        if (ac != 2)
            throw std::invalid_argument("Invalid input");
        check_input(av[1]);
        print_str(av[1], "av[1]");
        std::pair<vi, di> input = get_input(av[1]);
        vi vec = input.first;
        di deq = input.second;
        // print_vec(vec, "Before: ");
        print_vec(vec, "Vector: ");
        print_deque(deq, "Deque:  ");
        // PmergeMe::simpleSort(nbrs, 2);


        // Before: 3 5 9 7 4
        // After:  3 4 5 7 9
    }
    catch (std::exception &e) {
        std::cerr << "Error" <<std::endl;
    }
}
