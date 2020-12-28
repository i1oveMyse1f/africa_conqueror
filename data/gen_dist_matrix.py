import pandas
import typing as tp
import itertools
import os

def get_dist(i: str, j: str, normalize_dist: float, data_ij: pandas.DataFrame, cins: pandas.DataFrame) -> float:
    row = data_ij.loc[i, j]
    return cins[i] * cins[j] * ((1 - row['contig']) + (1 - row['comcol']) + row['dist'] / normalize_dist) / 3


def print_result(dist_matrix: tp.List[tp.List[float]]) -> None:
    n = len(dist_matrix)
    print(n)
    for line in dist_matrix:
        for i, d_ij in enumerate(line):
            print(d_ij, end='')
            if i + 1 == n:
                print()
            else:
                print(' ', end='')


def main() -> None:
    start_location = os.getcwd()
    data_cins = pandas.read_csv('data/africa_cins.csv', usecols=['country', 'short_name', 'CINS']).set_index(['short_name'])
    data_coniq_comcol_dist = pandas.read_excel('data/dist_cepii.xls').set_index(['iso_o', 'iso_d'])

    normalize_cins = data_cins['CINS'].max()
    data_cins = data_cins['CINS'].divide(normalize_cins)

    normalize_dist: float = 0
    for i, j in itertools.combinations(data_cins.index, 2):
        normalize_dist = max(normalize_dist,
                             data_coniq_comcol_dist.loc[i, j]['dist'])

    n = len(data_cins)
    assert n == 47

    dist_matrix = [[0 for i in range(0, n)] for j in range(0, n)]
    for first, second in itertools.combinations(enumerate(data_cins.index), 2):
        i, name_i = first
        j, name_j = second
        dist_matrix[i][j] = get_dist(name_i, name_j, normalize_dist, data_coniq_comcol_dist, data_cins)
        dist_matrix[j][i] = dist_matrix[i][j]
    print_result(dist_matrix)


if __name__ == '__main__':
    main()

