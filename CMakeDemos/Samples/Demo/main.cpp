#include <iostream>
#include "FileUtils.h"
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, int> ret;
        auto head = 0;
        for (auto num : nums) {
            auto div = target - num;
            auto ite = ret.find(div);
            if (ite != ret.end()) {
                return { ite->second, head};
            }
            ret[num] = head;
            ++head;
        }
        return {};
    }

    vector<int> twoSum1(vector<int>& nums, int target) {
        vector<int> ret;
        auto first = 0;
        for (auto num : nums) {
            auto div = target - num;
            auto iter = std::find(std::begin(nums) + first + 1, std::end(nums), div);
            if (iter != nums.end())
            {
                ret.emplace_back(first);
                ret.emplace_back(iter - nums.begin());
                return ret;
            }
            ++first;
        }

        return ret;
    }
};

int main(int argc, char *argv[])
{
    FileUtils::ins()->init("E:/WorkSpace/");
    std::cout << FileUtils::ins()->getPath("");

    bool a = true;
    bool b = true;

    auto ret = !a ^ b;

    auto src = std::vector<int> { 3, 2, 4 };
    auto value = Solution{}.twoSum(src, 6);
    return 0;
}
