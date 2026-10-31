#ifndef BANKER_H
#define BANKER_H
#include <vector>
bool isSafe(const std::vector<std::vector<int>>& allocation,
            const std::vector<std::vector<int>>& maximum,
            const std::vector<int>& available,
            std::vector<int>& safeSequence);
void bankerMenu();
#endif
