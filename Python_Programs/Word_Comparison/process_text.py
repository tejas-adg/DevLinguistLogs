import re, os, sys
import pandas as pd

def process_text_file(unproc, csv_file, str_col):
    rf = open(unproc)
    proc = os.path.join(os.path.abspath(os.path.join(unproc, '..')), os.path.basename(unproc).split('.')[0] + '_processed.txt')
    print(f'Saving processed text to {proc}')
    tf = open(proc, 'w')

    proc_text = rem_punc_string(rf.read())

    tf.write(proc_text)

    rf.close()
    tf.close()

    if ((csv_file is None) or (str_col is None)):
        sys.exit(0)

    try:
        df = pd.read_csv(csv_file).reset_index(drop = True)
        csv = True
    except UnicodeDecodeError:
        df = pd.read_excel(csv_file).reset_index(drop = True)
        csv = False

    insert_index = df.shape[0]

    df.loc[insert_index, 'String' + str(str_col)] = proc_text

    if csv:
        df.to_csv(csv_file, index = False)
    else:
        df.to_excel(csv_file, index = False)

def rem_punc_string(string):
    return re.sub('[!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~\n]+', '', string)


if __name__ == '__main__':

    raw_file = sys.argv[1]
    df_path = None
    col = None

    if len(sys.argv) > 2:
        df_path = sys.argv[2]
        col = sys.argv[3]

    process_text_file(raw_file, df_path, col)
