from PIL import Image

# 打开图片
image = Image.open('aha.bmp')

# 转换为黑白图片
bw_image = image.convert('L')

# 保存黑白图片
bw_image.save('aha_bw.bmp')
