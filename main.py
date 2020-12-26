import pandas
import typing as tp
import xlrd
import itertools

def get_dist(i: str, j: str, table: pandas.DataFrame) -> float:
    row = table[(table['iso_o'] == i) & (table['iso_d'] == j)].iloc[0]
    return (1 - row['comcol']) + row['dist'] + row['distw']


def main() -> None:
    africa_countries = {
        'Angola': 'AGO',
        'Botswana': 'BWA',
        'Burundi': 'BDI',
        'Congo': 'COG',
        'Democratic Republic of the Congo': 'COD',
        'Gabon': 'GAB',
        'Ghana': 'GHA',
        'Guinea-Bissau': 'GNB',
        'Kenya': 'KEN',
        'Lesotho': 'LSO',
        'Liberia': 'LBR',
        'Malawi': 'MWI',
        'Mauritius': 'MUS',
        'Mozambique': 'MOZ',
        'Namibia': 'NAM',
        'Rwanda': 'RWA',
        'Somalia': 'SOM',
        'South Africa': 'ZAF',
        'Swaziland': 'SWZ',
        'Tanzania': 'TZA',
        'Uganda': 'UGA',
        'Zambia': 'ZMB',
        'Zimbabwe': 'ZWE',
        'Algeria': 'DZA',
        'Benin': 'BEN',
        'Burkina Faso': 'BFA',
        'Cameroon': 'CMR',
        'Central African Republic': 'CAF',
        'Chad': 'TCD',
        'Cˆote d’Ivoire': 'CIV',
        'Djibouti': 'DJI',
        'Egypt': 'EGY',
        'Ethiopia': 'ETH',
        'Guinea': 'GIN',
        'Gambia': 'GMB',
        'Libya': 'LBY',
        'Madagascar': 'MDG',
        'Mali': 'MLI',
        'Mauritania': 'MRT',
        'Morocco': 'MAR',
        'Niger': 'NER',
        'Nigeria': 'NGA',
        'Senegal': 'SEN',
        'Sierra Leone': 'SLE',
        'Sudan': 'SDN',
        'Togo': 'TGO',
        'Tunisia': 'TUN'
    }

    n = len(africa_countries)
    table = pandas.read_excel('./dist_cepii.xls')

    result = [[0 for i in range(0, n)] for j in range(0, n)]
    for first, second in itertools.combinations(enumerate(africa_countries.items()), 2):
        i, name_i = first
        big_i, short_i = name_i
        j, name_j = second
        big_j, short_j = name_j
        result[i][j] = get_dist(short_i, short_j, table)
        result[j][i] = result[i][j]
    print(result)


if __name__ == '__main__':
    main()
