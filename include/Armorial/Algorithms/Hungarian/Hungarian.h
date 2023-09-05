#ifndef ARMORIAL_ALGORITHMS_HUNGARIAN_H
#define ARMORIAL_ALGORITHMS_HUNGARIAN_H

#include <Armorial/Algorithms/Hungarian/impl/hungarian_impl.h>

namespace Algorithms {
template <class R, class PT> class Hungarian {
public:
  inline static QVector<QPair<R, PT>> match(const QVector<R> &robots,
                                            const QVector<PT> &positions) {
    QVector<QPair<R, PT>> result;
    if (!(robots.size() <= positions.size())) {
      return result;
    }
    const int n = static_cast<int>(robots.size());
    const int m = static_cast<int>(positions.size());

    tourist::hungarian<float> hungarian(n, m);

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        R robot = robots[i];
        hungarian.a[i][j] = robot.distTo(positions[j]);
      }
    }

    hungarian.solve();

    for (int i = 0; i < n; ++i) {
      const auto &position = positions[hungarian.pa[i]];
      result.push_back(QPair<R, PT>(std::move(robots[i]), position));
      // result.emplace_back(QPair<R, PT>(std::move(robots[i]), position));
    }

    return result;
  }
};
} // namespace Algorithms

#endif // ARMORIAL_ALGORITHMS_HUNGARIAN_H
