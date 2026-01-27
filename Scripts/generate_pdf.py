#!/usr/bin/env python
import json
import sys
import os

def generate_pdf(json_path, pdf_path):
    try:
        with open(json_path, 'r', encoding='utf-8') as f:
            config = json.load(f)
        
        def escape(s):
            s = str(s)
            return s.replace(chr(92), chr(92)*2).replace('(', chr(92)+'(').replace(')', chr(92)+')')
        
        lines = []
        lines.append('BT')
        lines.append('/F2 16 Tf')
        lines.append('50 750 Td')
        lines.append('(Product Configuration Summary) Tj')
        lines.append('0 -25 Td /F1 11 Tf')
        lines.append('(Configuration: %s) Tj' % escape(config.get('configurationName', 'N/A')))
        lines.append('0 -18 Td')
        lines.append('(Timestamp: %s) Tj' % escape(config.get('timestamp', 'N/A')))
        lines.append('0 -30 Td /F2 12 Tf')
        lines.append('(Selected Variants:) Tj')
        lines.append('0 -20 Td /F1 10 Tf')
        
        variants = config.get('selectedVariants', [])
        for i, variant in enumerate(variants[:30]):
            lines.append('(  %d. %s) Tj 0 -14 Td' % (i+1, escape(variant)))
        
        if len(variants) > 30:
            lines.append('(  ... and %d more) Tj 0 -14 Td' % (len(variants) - 30))
        
        lines.append('0 -20 Td /F2 11 Tf')
        lines.append('(Environment: %s) Tj' % escape(config.get('selectedEnvironment', 'N/A')))
        lines.append('0 -18 Td')
        lines.append('(Camera: %s) Tj' % escape(config.get('selectedCamera', 'N/A')))
        lines.append('ET')
        
        stream = chr(10).join(lines)
        stream_bytes = stream.encode('latin-1')
        stream_len = len(stream_bytes)
        
        pdf = []
        pdf.append('%PDF-1.4')
        pdf.append('1 0 obj')
        pdf.append('<< /Type /Catalog /Pages 2 0 R >>')
        pdf.append('endobj')
        pdf.append('2 0 obj')
        pdf.append('<< /Type /Pages /Kids [3 0 R] /Count 1 >>')
        pdf.append('endobj')
        pdf.append('3 0 obj')
        pdf.append('<<')
        pdf.append('/Type /Page')
        pdf.append('/Parent 2 0 R')
        pdf.append('/MediaBox [0 0 612 792]')
        pdf.append('/Contents 4 0 R')
        pdf.append('/Resources <<')
        pdf.append('/Font <<')
        pdf.append('/F1 << /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>')
        pdf.append('/F2 << /Type /Font /Subtype /Type1 /BaseFont /Helvetica-Bold >>')
        pdf.append('>>')
        pdf.append('>>')
        pdf.append('>>')
        pdf.append('endobj')
        pdf.append('4 0 obj')
        pdf.append('<< /Length %d >>' % stream_len)
        pdf.append('stream')
        pdf.append(stream)
        pdf.append('endstream')
        pdf.append('endobj')
        pdf.append('xref')
        pdf.append('0 5')
        pdf.append('0000000000 65535 f')
        pdf.append('0000000009 00000 n')
        pdf.append('0000000058 00000 n')
        pdf.append('0000000115 00000 n')
        pdf.append('0000000344 00000 n')
        pdf.append('trailer')
        pdf.append('<< /Size 5 /Root 1 0 R >>')
        pdf.append('startxref')
        pdf.append(str(400 + stream_len))
        pdf.append('%%EOF')
        
        os.makedirs(os.path.dirname(pdf_path), exist_ok=True)
        with open(pdf_path, 'wb') as f:
            f.write((chr(10).join(pdf)).encode('latin-1'))
        
        print('PDF generated: %s' % pdf_path)
        return True
    except Exception as e:
        print('ERROR: %s' % str(e))
        import traceback
        traceback.print_exc()
        return False

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('Usage: python generate_pdf.py <json_path> <pdf_path>')
        sys.exit(1)
    success = generate_pdf(sys.argv[1], sys.argv[2])
    sys.exit(0 if success else 1)
