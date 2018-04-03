from os import listdir
from os.path import isfile, join
import pandas as pd
import sys

def count_names(file):
    name = file.split('.')[0]
    count = 0
    with open('./data/' + file, 'r') as f:
        count = len(f.readlines())

    return name, count

def main():
    txtfiles = [(f if '.txt' in f else None) for f in listdir('./data') if isfile(join('./data', f))]
    txtfiles.remove(None)

    df = pd.DataFrame()
    names = []
    doccounts = []
    for file in txtfiles:
        out = count_names(file)
        names.append(out[0])
        doccounts.append(out[1])
    df['queries'] = names
    df['doccounts'] = doccounts

    df = df.sort_values(by='doccounts')
    
    



if __name__ == '__main__':
    main() 
