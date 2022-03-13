#include "grader.h"

#include <iostream>
#include <string>

namespace {

bool has_lcp(const int& K, const std::string& s, const int& len) {
	std::string q = s;
	for (int i = len; i < K; ++i)
		q[i] = '_';

	auto [mns, mxs] = get_min_max(q);

	return (mns.size() != 0);
}

} // namespace

// to compile: g++ grader.cpp solution.cpp -o test.exe
std::string find_next(std::string str) {

	int K = str.size();

	if (has_lcp(K, str, K)) {
		return str;
	}

	int lcp_len = 0;
	for (int l = K; l > 0; l >>= 1) {
		if (has_lcp(K, str, lcp_len + l))
			lcp_len += l;
	}

	for (; lcp_len >= 0; --lcp_len) {
		std::string guess = str;
		guess[lcp_len] = '?';
		for (int i = lcp_len + 1; i < K; ++i)
			guess[i] = '_';
		
		auto [mns, mxs] = get_min_max(guess);

		//std::cerr << "LCP length: " << lcp_len << std::endl;
		//std::cerr << "Guessing: " << guess << std::endl;
		//std::cerr << "Get: " << mns << ' ' << mxs << std::endl;

		if (mxs.size() == K and mxs[lcp_len] > str[lcp_len])
			break;
	}

	//std::cerr << "LCP length: " << lcp_len << std::endl;

	if (lcp_len == -1) {
		return std::string("");
	}

	std::string ans;

	for (const char& c: {'A', 'C', 'G', 'T'}) {
		std::string guess = str;
		if (c <= str[lcp_len])
			continue;
		guess[lcp_len] = c;
		if (has_lcp(K, guess, lcp_len + 1)) {
			ans = guess;
			break;
		}
	}

	for (int i = lcp_len + 1; i < K; ++i)
		ans[i] = '?';

	//std::cerr << "Ans: " << ans << std::endl;

	auto [mns, mxs] = get_min_max(ans);

	return mns;
}
