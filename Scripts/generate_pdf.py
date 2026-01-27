#!/usr/bin/env python
import json
import sys
import os

def generate_pdf(json_path, pdf_path):
    try:
        with open(json_path, 'r', encoding='utf-8') as f:
            config = json.load(f)
        
        # Build minimal PDF
        pdf_lines = ['%PDF-1.4']
        pdf_lines.append('1 0 obj')
        pdf_lines.append('<< /Type /Catalog /Pages 2 0 R >>')
        pdf_lines.append('endobj')
        pdf_lines.append('2 0 obj')
        pdf_lines.append('<< /Type /Pages /Kids [3 0 R] /Count 1 >>')
        pdf_lines.append('endobj')
        pdf_lines.append('3 0 obj')
        pdf_lines.append('<<')
        pdf_lines.append('/Type /Page')
        pdf_lines.append('/Parent 2 0 R')
        pdf_lines.append('/MediaBox [0 0 612 792]')
        pdf_lines.append('/Contents 4 0 R')
        pdf_lines.append('/Resources << /Font << /F1 << /Type /Font /Subtype /Type1 /BaseFont /Helvetica >> >> >>')
        pdf_lines.append('>>')
        pdf_lines.append('endobj')
        
        # Content
        content = 'BT /F1 12 Tf 50 750 Td (Configuration: ' + config.get('configurationName', 'N/A') + ') Tj ET'
        pdf_lines.append('4 0 obj')
        pdf_lines.append('<< /Length ' + str(len(content)) + ' >>')
        pdf_lines.append('stream')
        pdf_lines.append(content)
        pdf_lines.append('endstream')
        pdf_lines.append('endobj')
        
        # XRef and trailer
        xref_pos = sum(len(line) + 1 for line in pdf_lines)
        pdf_lines.append('xref')
        pdf_lines.append('0 5')
        pdf_lines.append('0000000000 65535 f')
        pdf_lines.append('0000000009 00000 n')
        pdf_lines.append('0000000058 00000 n')
        pdf_lines.append('0000000115 00000 n')
        pdf_lines.append('0000000300 00000 n')
        pdf_lines.append('trailer')
        pdf_lines.append('<< /Size 5 /Root 1 0 R >>')
        pdf_lines.append('startxref')
        pdf_lines.append(str(xref_pos))
        pdf_lines.append('%%EOF')
        
        os.makedirs(os.path.dirname(pdf_path), exist_ok=True)
        with open(pdf_path, 'w', encoding='latin-1') as f:
            for line in pdf_lines:
                f.write(line + chr(10))
        
        print('PDF generated: ' + pdf_path)
        return True
    except Exception as e:
        print('ERROR: ' + str(e))
        return False

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('Usage: python generate_pdf.py <json_path> <pdf_path>')
        sys.exit(1)
    success = generate_pdf(sys.argv[1], sys.argv[2])
    sys.exit(0 if success else 1)
