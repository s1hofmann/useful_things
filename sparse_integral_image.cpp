#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include "opencv2/imgproc/imgproc.hpp"

bool equals(const cv::Mat1f &mat1, const cv::Mat1f &mat2)
{
    if(mat1.rows != mat2.rows || mat1.cols != mat2.cols) {
        return false;
    }

    cv::Scalar s = cv::sum(mat1 - mat2);

    if(s[0] == 0) {
        return true;
    } else {
        return false;
    }
}

int main(void) {
    std::unordered_map<int, std::unordered_map<int, cv::Mat1f>> map;

    map[2][1] = cv::Mat1f::ones(1, 1);
    map[3][1] = cv::Mat1f::ones(1, 1);
    map[3][1] *= 2;
    map[4][3] = cv::Mat1f::ones(1, 1);
    map[5][3] *= 4;
    map[7][4] = cv::Mat1f::ones(1, 1);
    map[3][7] = cv::Mat1f::ones(1, 1);

    std::cout << "before:" << std::endl;

    for(int r = 0; r < 8; ++r) {
        for(int c = 0; c < 8; ++c) {
            if(map[r][c].empty()) {
                std::cout << cv::Mat1f::zeros(1, 1);
            } else {
                std::cout << map[r][c];
            }
        }
        std::cout << std::endl;
    }

    if(map[0][0].empty()) {
        map[0][0] = cv::Mat1f::zeros(1, 1);
    }

    cv::Mat_<cv::Mat1f*> mapping(8, 8);
    mapping.at<cv::Mat1f*>(0, 0) = &map[0][0];

    for(int r = 1; r < 8; ++r) {
        cv::Mat1f lastElement = *(mapping.at<cv::Mat1f*>(r - 1, 0));
        if(!map[r][0].empty()) {
            map[r][0] += lastElement;
            mapping.at<cv::Mat1f*>(r, 0) = &map[r][0];
        } else {
            mapping.at<cv::Mat1f*>(r, 0) = mapping.at<cv::Mat1f*>(r - 1, 0);
        }
    }

    for(int c = 1; c < 8; ++c) {
        cv::Mat1f lastElement = *(mapping.at<cv::Mat1f*>(0, c - 1));
        if(!map[0][c].empty()) {
            map[0][c] += lastElement;
            mapping.at<cv::Mat1f*>(0, c) = &map[0][c];
        } else {
            mapping.at<cv::Mat1f*>(0, c) = mapping.at<cv::Mat1f*>(0, c - 1);
        }
    }

    for(int r = 1; r < 8; ++r) {
        for(int c = 1; c < 8; ++c) {
            cv::Mat1f lastLeft = *(mapping.at<cv::Mat1f*>(r, c - 1));
            cv::Mat1f lastTop = *(mapping.at<cv::Mat1f*>(r - 1, c));
            cv::Mat1f lastTopLeft = *(mapping.at<cv::Mat1f*>(r - 1, c - 1));

            cv::Mat1f tmp;

            if(!map[r][c].empty()) {
                tmp = map[r][c] + lastLeft + lastTop - lastTopLeft;
            } else {
                tmp = lastLeft + lastTop - lastTopLeft;
            }

            cv::Scalar s = cv::sum(tmp - lastLeft);

            if(equals(tmp, lastLeft)) {
                mapping.at<cv::Mat1f*>(r, c) = mapping.at<cv::Mat1f*>(r, c - 1);
            } else {
                if(equals(tmp, lastTop)) {
                    std::cout << "Value changed, top entry equal" << std::endl;
                    mapping.at<cv::Mat1f*>(r, c) = mapping.at<cv::Mat1f*>(r - 1, c);
                } else {
                    std::cout << "Value changed, new value" << std::endl;
                    map[r][c] = tmp;
                    mapping.at<cv::Mat1f*>(r, c) = &map[r][c];
                }
            }
        }
    }

    std::cout << "after:" << std::endl;

    for(int r = 0; r < 8; ++r) {
        for(int c = 0; c < 8; ++c) {
            if(map[r][c].empty()) {
                std::cout << cv::Mat1f::zeros(1, 1);
            } else {
                std::cout << map[r][c];
            }
        }
        std::cout << std::endl;
    }

    std::cout << "mapping:" << std::endl;
    for(int y = 0; y < mapping.rows; ++y) {
        for(int x = 0; x < mapping.cols; ++x) {
            std::cout << "(" << mapping.at<cv::Mat1f*>(y, x) << "," << mapping.at<cv::Mat1f*>(y, x) << ")";
        }
        std::cout << std::endl;
    }
    
    std::cout << "result:" << std::endl;
    for(int y = 0; y < mapping.rows; ++y) {
        for(int x = 0; x < mapping.cols; ++x) {
            std::cout << *mapping.at<cv::Mat1f*>(y, x);
        }
        std::cout << std::endl;
    }

    cv::Mat1f result;
    result = (*mapping.at<cv::Mat1f*>(4, 4) - *mapping.at<cv::Mat1f*>(0, 4) - *mapping.at<cv::Mat1f*>(4, 0) + *mapping.at<cv::Mat1f*>(0, 0));

    std::cout << result << std::endl;

    return 0;
}
