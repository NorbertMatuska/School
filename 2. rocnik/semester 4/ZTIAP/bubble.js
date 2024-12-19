function bubbleSort(arr) {
    
    for(var k = 0; k < arr.length; k++){
     
        for(var j = 0; j < ( arr.length - k -1 ); j++){
            
          if(arr[j] > arr[j+1]){
              
            var temp = arr[j]
            arr[j] = arr[j + 1]
            arr[j+1] = temp
          }
        }
      }
    
    console.log(arr);
    /*const ppp = new Array()
    var f = 0;
    for (i = 0; i < 5; i++) {
        ppp.push(f);
        f += 1;
    }
    console.log(ppp)*/
    }

    const arr = new Array(1,5,6,7,8,9,8,5,12,3,46,78,2,465,32,4,16,21,19,64);
    console.log("Unsorted array:");
    console.log(arr);
    console.log("Sorted array:");
    bubbleSort(arr);

    function snake() {
        var i = 2;
        var j = 3;
        const arr1 = new Array();
        const arr2 = new Array();
        var temp = 1;
        var temp2 = 0;

        for (var k = 0; k < i; k++) {
            for (var l = 0; l < j; l++) {
                if (k % 2 == 0) {
                    if(k > 1 && l == 0) {temp = temp2 + j;}
                    arr2.push(temp)
                    temp += 1;
                    console.log(arr2);
                }
                else {
                    if(l == 0) {temp = temp + j - 1;}
                    if(l == (j-1)) {temp2 = temp;}
                    arr2.push(temp)
                    temp -= 1;
                    console.log(arr2);
                }
            }
            arr1.push(arr2)
        }
        console.log(arr1)
    }
    snake()