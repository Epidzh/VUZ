def first():
    pass


def second():
    pass


def third():
    pass


def get_group(data):
    pass


def get_data_from_docx():
    from docx import Document
    doc = Document('1.docx')
    data = []
    for row in doc.tables[0].rows:
        for cell in row.cells:
            if cell.text != '':
                data.append(float(cell.text.replace(",", ".")))
    return data


data = get_data_from_docx()
first()
second()
third()
