//
//  main.cpp
//  spatial_partitioning
//
//  Created by Junchen Zhang on 6/20/18.
//  Copyright © 2018 Junchen Zhang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "QuadTree.hpp"
#include "Generators.hpp"
#include "BucketKNN.hpp"
#include "KDTree.hpp"
#include "Point.hpp"
#include "Stopwatch.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
//    ofstream file;
//    file.open("bucket.csv");
//    file << "K,Dimension,Number of Points,Time,Distribution" << endl;
//
//    auto gen = UniformGenerator<1>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<1>(n, 100, gen);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            BucketKNN<1> bk = BucketKNN<1>(data.training, 5);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                bk.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file << k << ",1," << n << "," << avg_time << ",Uniform" << endl;
//        }
//    }
//    auto gen2 = GaussianGenerator<1>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<1>(n, 100, gen2);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            BucketKNN<1> bk = BucketKNN<1>(data.training, 5);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                bk.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file << k << ",1," << n << "," << avg_time << ",Gaussian" << endl;
//        }
//    }
//    auto gen3 = UniformGenerator<2>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<2>(n, 100, gen3);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            BucketKNN<2> bk = BucketKNN<2>(data.training, 5);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                bk.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file << k << ",2," << n << "," << avg_time << ",Uniform" << endl;
//        }
//    }
//    auto gen4 = GaussianGenerator<2>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<2>(n, 100, gen4);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            BucketKNN<2> bk = BucketKNN<2>(data.training, 5);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                bk.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file << k << ",2," << n << "," << avg_time << ",Gaussian" << endl;
//        }
//    }
//    auto gen5 = UniformGenerator<3>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<3>(n, 100, gen5);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            BucketKNN<3> bk = BucketKNN<3>(data.training, 5);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                bk.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file << k << ",3," << n << "," << avg_time << ",Uniform" << endl;
//        }
//    }
//    auto gen6 = GaussianGenerator<3>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<3>(n, 100, gen6);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            BucketKNN<3> bk = BucketKNN<3>(data.training, 5);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                bk.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file << k << ",3," << n << "," << avg_time << ",Gaussian" << endl;
//        }
//    }
//    auto gen7 = UniformGenerator<4>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<4>(n, 100, gen7);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            BucketKNN<4> bk = BucketKNN<4>(data.training, 5);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                bk.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file << k << ",4," << n << "," << avg_time << ",Uniform" << endl;
//        }
//    }
//    auto gen8 = GaussianGenerator<4>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<4>(n, 100, gen8);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            BucketKNN<4> bk = BucketKNN<4>(data.training, 5);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                bk.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file << k << ",4," << n << "," << avg_time << ",Gaussian" << endl;
//        }
//    }
//    file.close();
    
    
//    ofstream file2;
//    file2.open("kdtree.csv");
//    file2 << "K,Dimension,Number of Points,Time,Distribution" << endl;
//
//    auto gen = UniformGenerator<1>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<1>(n, 100, gen);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            KDTree<1> kt = KDTree<1>(data.training);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                kt.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file2 << k << ",1," << n << "," << avg_time << ",Uniform" << endl;
//        }
//    }
//    auto gen2 = GaussianGenerator<1>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<1>(n, 100, gen2);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            KDTree<1> kt = KDTree<1>(data.training);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                kt.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file2 << k << ",1," << n << "," << avg_time << ",Gaussian" << endl;
//        }
//    }
//    auto gen3 = UniformGenerator<2>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<2>(n, 100, gen3);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            KDTree<2> kt = KDTree<2>(data.training);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                kt.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file2 << k << ",2," << n << "," << avg_time << ",Uniform" << endl;
//        }
//    }
//    auto gen4 = GaussianGenerator<2>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<2>(n, 100, gen4);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            KDTree<2> kt = KDTree<2>(data.training);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                kt.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file2 << k << ",2," << n << "," << avg_time << ",Gaussian" << endl;
//        }
//    }
//    auto gen5 = UniformGenerator<3>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<3>(n, 100, gen5);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            KDTree<3> kt = KDTree<3>(data.training);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                kt.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file2 << k << ",3," << n << "," << avg_time << ",Uniform" << endl;
//        }
//    }
//    auto gen6 = GaussianGenerator<3>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<3>(n, 100, gen6);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            KDTree<3> kt = KDTree<3>(data.training);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                kt.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file2 << k << ",3," << n << "," << avg_time << ",Gaussian" << endl;
//        }
//    }
//    auto gen7 = UniformGenerator<4>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<4>(n, 100, gen7);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            KDTree<4> kt = KDTree<4>(data.training);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                kt.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file2 << k << ",4," << n << "," << avg_time << ",Uniform" << endl;
//        }
//    }
//    auto gen8 = GaussianGenerator<4>(-1, 1);
//    for (int n = 50; n < 1000000; n *= 2) {
//        auto data = getTrialData<4>(n, 100, gen8);
//        for (int k = 1; k <= 11; ++k) {
//            double avg_time = 0;
//            KDTree<4> kt = KDTree<4>(data.training);
//            for (int i = 0; i < 10; ++i) {
//                Stopwatch clock;
//                clock.start();
//                kt.KNN(data.testing[i], k);
//                avg_time += clock.stop();
//            }
//            avg_time /= 10;
//            file2 << k << ",4," << n << "," << avg_time << ",Gaussian" << endl;
//        }
//    }
//    file2.close();
    
    
//        ofstream file3;
//        file3.open("quadtree.csv");
//        file3 << "K,Dimension,Number of Points,Time,Distribution" << endl;
//
//        auto gen3 = UniformGenerator<2>(-1, 1);
//        for (int n = 50; n < 1000000; n *= 2) {
//            auto data = getTrialData<2>(n, 100, gen3);
//            for (int k = 1; k <= 11; ++k) {
//                double avg_time = 0;
//                QuadTree qt = QuadTree(data.training, 3);
//                for (int i = 0; i < 10; ++i) {
//                    Stopwatch clock;
//                    clock.start();
//                    qt.KNN(data.testing[i], k);
//                    avg_time += clock.stop();
//                }
//                avg_time /= 10;
//                file3 << k << ",2," << n << "," << avg_time << ",Uniform" << endl;
//            }
//        }
//        auto gen4 = GaussianGenerator<2>(-1, 1);
//        for (int n = 50; n < 1000000; n *= 2) {
//            auto data = getTrialData<2>(n, 100, gen4);
//            for (int k = 1; k <= 11; ++k) {
//                double avg_time = 0;
//                QuadTree qt = QuadTree(data.training, 3);
//                for (int i = 0; i < 10; ++i) {
//                    Stopwatch clock;
//                    clock.start();
//                    qt.KNN(data.testing[i], k);
//                    avg_time += clock.stop();
//                }
//                avg_time /= 10;
//                file3 << k << ",2," << n << "," << avg_time << ",Gaussian" << endl;
//            }
//        }
//        file3.close();
}

