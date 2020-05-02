from scipy.stats import norm, t
from math import sqrt, fabs


def save_table_to_docx(data, file_name):
    import docx
    pass
    try:
        doc = docx.Document(file_name)
    except docx.opc.exceptions.PackageNotFoundError:
        doc = docx.Document()
    table = doc.add_table(rows=len(data), cols=len(data[0]))
    # table.style = 'TableGrid'
    i, j = 0, 0
    for row in data:
        for item in row:
            table.rows[i].cells[j % len(data[0])].text = str(item)
            j += 1
            if j % len(data[0]) == 0:
                j = 0
                i += 1
    doc.add_paragraph()
    doc.save(file_name)


def get_data_from_docx(file_name):
    from docx import Document
    doc = Document(file_name)
    data = []
    for row in doc.tables[0].rows:
        for cell in row.cells:
            if cell.text != '':
                data.append(float(cell.text.replace(",", ".")))
    return data


def get_table_from_docx(file_name):
    from docx import Document
    doc = Document(file_name)
    data = [[],]
    for row in doc.tables[0].rows:
        for cell in row.cells:
            if cell.text != '':
                data[-1].append(float(cell.text.replace(",", ".")))
        data.append([])
    return data


def first(data, a, sigma):
    alpha = 0.05
    norm1 = norm(0, 1)
    N = len(data)
    u1 = sum(data) / N
    c = a + (sigma / sqrt(N)) * (1 / (norm1.pdf(1 - alpha)))
    print("U1 = ", u1)
    print("C = ", c)
    table = []
    if u1 <= c:
        print("Принимаемая гипотеза - H0")
        table = [[' ', ' ', ' ', 'Принятая гипотеза'], ["%.6f" % u1, 0.05, "%.6f" % c, "H0"]]
    else:
        print("Принимаемая гипотеза - H1")
        table = [[' ', ' ', ' ', 'Принятая гипотеза'], ["%.6f" % u1, 0.05, "%.6f" % c, "H1"]]
    save_table_to_docx(table, "results1.docx")


def get_tnm(N, M, sr1, sr2, disp1, disp2):
    return ((sr1 - sr2) / sqrt(N * (disp1 - sr1**2) + M * (disp2 - sr2**2))) * sqrt(M * N * (N + M - 2) / (N + M))


def second(data):
    data1, data2, data3 = [], [], []
    N = len(data) // 3
    print(N)
    for i in enumerate(data):
        if i[0] % 3 == 0:
            data1.append(i[1])
        elif i[0] % 3 == 1:
            data2.append(i[1])
        else:
            data3.append(i[1])

    sr1 = sum(data1) / len(data1)
    sr2 = sum(data2) / len(data2)
    sr3 = sum(data3) / len(data3)

    disp1 = sum([i**2 for i in data1]) / len(data1)
    disp2 = sum([i**2 for i in data2]) / len(data2)
    disp3 = sum([i**2 for i in data3]) / len(data3)

    s1 = (len(data1) / (len(data1) - 1)) * (disp1 - sr1**2)
    s2 = (len(data2) / (len(data2) - 1)) * (disp2 - sr2**2)
    s3 = (len(data3) / (len(data3) - 1)) * (disp3 - sr3**2)

    tnm12 = get_tnm(len(data1), len(data2), sr1, sr2, disp1, disp2)
    tnm13 = get_tnm(len(data1), len(data3), sr1, sr3, disp1, disp3)
    tnm23 = get_tnm(len(data2), len(data3), sr2, sr3, disp2, disp3)

    table = list()
    table.append(["%.6f" % sr1, "%.6f" % sr2, "%.6f" % disp1, "%.6f" % disp2, "%.6f" % s1, "%.6f" % s2, "%.6f" % tnm12])
    table.append(["%.6f" % sr1, "%.6f" % sr3, "%.6f" % disp1, "%.6f" % disp3, "%.6f" % s1, "%.6f" % s3, "%.6f" % tnm13])
    table.append(["%.6f" % sr2, "%.6f" % sr3, "%.6f" % disp2, "%.6f" % disp3, "%.6f" % s2, "%.6f" % s3, "%.6f" % tnm23])

    save_table_to_docx(table, 'results2.docx')

    table = [[], [], []]
    tinv = float("%.6f" % t.ppf(0.975, 2 * N - 2))
    table[0] = ["%.6f" % fabs(tnm12), tinv]
    table[0].append("ВЕРНА" if fabs(tnm12) <= tinv else "НЕВЕРНА")

    table[1] = ["%.6f" % fabs(tnm13), tinv]
    table[1].append("ВЕРНА" if fabs(tnm13) <= tinv else "НЕВЕРНА")

    table[2] = ["%.6f" % fabs(tnm23), tinv]
    table[2].append("ВЕРНА" if fabs(tnm23) <= tinv else "НЕВЕРНА")

    save_table_to_docx(table, 'results2.docx')


a = 6.1
sigma = 1.46
data = get_data_from_docx('1.docx')
table = get_table_from_docx('1.docx')
save_table_to_docx(table, 'results1.docx')
print(data)
first(data, a, sigma)

data = get_data_from_docx('2.docx')
table = get_table_from_docx('2.docx')
save_table_to_docx(table, 'results2.docx')
print(data)
second(data)
