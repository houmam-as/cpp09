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
#include <utility>
#include <deque>

typedef std::vector<int> vi;
typedef std::vector< std::vector<int> > vvi;
typedef std::vector< std::pair<vi, vvi::iterator > > vp;
typedef std::deque <int> di;


// template <typename VI>
class PmergeMe {
    // private:
    public:
        static void simpleSort(vi& toSort, int pairSize);
        static void print_vec(vi& toSort);
        // static void calculate(std::string input);
};

#endif
