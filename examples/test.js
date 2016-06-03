var cv = require('../lib/opencv');

var mat = new cv.Matrix(1, 2, cv.Constants.CV_8U, [1]);
var row = mat.pixelRow(0);
console.log("mat: " + row[0] + ', ' + row[1]);
console.log('replace')
mat.replace(5, 1)
row = mat.pixelRow(0);
console.log("mat: " + row[0] + ', ' + row[1]);

var yml = mat.yml()
//console.log(yml)
var m = cv.fromYml(yml)
//console.log(m.width())
