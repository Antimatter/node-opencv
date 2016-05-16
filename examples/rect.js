var cv = require('../lib/opencv');
var r = new cv.Rect(0, 0, 1, 1)
var p = new cv.Point(0,3)
console.log(r.width)
console.log('GC_BGD: ' + cv.Constants.GC_BGD)
console.log('GC_FGD: ' + cv.Constants.GC_FGD)
console.log('GC_PR_BGD: ' + cv.Constants.GC_PR_BGD)
console.log('GC_PR_FGD: ' + cv.Constants.GC_PR_FGD)
