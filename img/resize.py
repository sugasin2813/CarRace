import cv2

src = cv2.imread("./goal.jpg")

dst = cv2.resize(src,(200,80))

cv2.imwrite("./out.jpg",dst)
