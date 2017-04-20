#ifndef QL_HPP
#define QL_HPP

#include <map>
#include <algorithm>
#include <iostream>

namespace enhuiz
{
namespace model
{
class QL
{
  public:
    QL(int nAction, float alpha, float gamma) : nAction(nAction), alpha(alpha), gamma(gamma) {}

    void reward(std::string prevS, std::string currS, int action, float R)
    {
        if (Q.count(prevS) > 0)
        {
            Q[prevS][action] = (1 - alpha) * Q[prevS][action] + alpha * (R + gamma * getMax(currS));
        }
        else
        {
            Q[prevS] = std::vector<float>(nAction);
            Q[prevS][action] = (1 - alpha) * Q[prevS][action] + alpha * (R + gamma * getMax(currS));
            std::cerr << "New State " << prevS << " " << currS << " " << Q[prevS][action] << std::endl;
        }
    }

    float getMax(std::string state)
    {
        float ret = 0;
        if (Q.count(state) > 0)
        {
            ret = *std::max_element(Q[state].begin(), Q[state].end());
        }
        return ret;
    }

    int getArgMax(std::string state)
    {
        int ret = 0;
        if (Q.count(state) > 0)
        {
            auto it = std::max_element(Q[state].begin(), Q[state].end());
            ret = std::distance(Q[state].begin(), it);
        }
        return ret;
    }

  private:
    std::map<std::string, std::vector<float>> Q;

    int nAction;
    float alpha;
    float gamma;
};
}
}

#endif