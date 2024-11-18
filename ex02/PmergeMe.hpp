/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-sal <hait-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:52:48 by hait-sal          #+#    #+#             */
/*   Updated: 2024/11/03 13:39:29 by hait-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>


class PmergeMe {
    // private:
    public:
        static void simpleSort(std::vector<int>& toSort, int pairSize);
        static void print_vec(std::vector<int>& toSort);
        // static void calculate(std::string input);
};

#endif