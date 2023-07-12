from Crypto.Cipher import AES

encrypted_firmware = open("./encrypted_firmware","rb").read()

cipher = AES.new(b"\x87\xdf\x86\xf0\xba\x4e\x95\xda\xe9\x4b\xe9\x85\x60\x9f\x31\xa7", AES.MODE_CBC,b"\x6e\x33\x29\xc58\xcf\xca9\xec\x3a\x07\x42\x27\x3d\xad\x68")
decryped_firmware = cipher.decrypt(encrypted_firmware)

open("./decrypted_firmware","wb").write(decryped_firmware)

