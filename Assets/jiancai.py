import cv2 as cv

row = 4
column = 4

org_img = cv.imread("/home/esoman/c++code/Game/game02/Assets/sucai.PNG")
height, width = org_img.shape[:2]
print('height %d widht %d' % (height, width))

row_step = (int)(height/row)
column_step = (int)(width/column)

print('row step %d col step %d'% (row_step, column_step))

print('height %d widht %d' % (row_step*row, column_step*column))

img = org_img[0:row_step*row, 0:column_step*column]

for i in range(row):
    for j in range(column):
        pic_name = "/home/esoman/" + str(i) + "_" + str(j) + ".jpeg"
        tmp_img = img[(i*row_step):(i*row_step+row_step), (j*column_step):(j*column_step)+column_step]
        cv.imwrite(pic_name, tmp_img)



