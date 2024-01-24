import pandas as pd

def group_data(df, column, key):
    grouped = df.groupby(column).agg({
        'Byte Count': ['sum'],
        'Packet Count': ['sum']
    }).reset_index()
    grouped.columns = ['IP', f'{key} Bytes', f'{key} Packets']
    return grouped
def process_csv(input_file, output_file):
    df = pd.read_csv(input_file)
    grouped_src = group_data(df, 'Source IP', 'Transmitted')
    grouped_dst = group_data(df, 'Destination IP', 'Received')
    merged_data = pd.merge(grouped_src, grouped_dst, how='outer', on="IP").fillna(0)

    numeric_columns = ['Transmitted Bytes', 'Transmitted Packets', 'Received Bytes', 'Received Packets']
    merged_data[numeric_columns] = merged_data[numeric_columns].map(lambda x: int(x) if pd.notnull(x) else x)

    merged_data.to_csv(output_file, index=False)


if __name__ == "__main__":
    process_csv("../first_program.csv", "../second_program.csv")

