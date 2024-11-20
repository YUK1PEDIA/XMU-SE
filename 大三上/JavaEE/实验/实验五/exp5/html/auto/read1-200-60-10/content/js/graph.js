/*
   Licensed to the Apache Software Foundation (ASF) under one or more
   contributor license agreements.  See the NOTICE file distributed with
   this work for additional information regarding copyright ownership.
   The ASF licenses this file to You under the Apache License, Version 2.0
   (the "License"); you may not use this file except in compliance with
   the License.  You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
$(document).ready(function() {

    $(".click-title").mouseenter( function(    e){
        e.preventDefault();
        this.style.cursor="pointer";
    });
    $(".click-title").mousedown( function(event){
        event.preventDefault();
    });

    // Ugly code while this script is shared among several pages
    try{
        refreshHitsPerSecond(true);
    } catch(e){}
    try{
        refreshResponseTimeOverTime(true);
    } catch(e){}
    try{
        refreshResponseTimePercentiles();
    } catch(e){}
});


var responseTimePercentilesInfos = {
        data: {"result": {"minY": 6.0, "minX": 0.0, "maxY": 1331.0, "series": [{"data": [[0.0, 6.0], [0.1, 8.0], [0.2, 14.0], [0.3, 14.0], [0.4, 14.0], [0.5, 14.0], [0.6, 14.0], [0.7, 14.0], [0.8, 14.0], [0.9, 14.0], [1.0, 15.0], [1.1, 15.0], [1.2, 15.0], [1.3, 15.0], [1.4, 15.0], [1.5, 15.0], [1.6, 15.0], [1.7, 15.0], [1.8, 15.0], [1.9, 15.0], [2.0, 15.0], [2.1, 15.0], [2.2, 15.0], [2.3, 15.0], [2.4, 15.0], [2.5, 15.0], [2.6, 15.0], [2.7, 15.0], [2.8, 15.0], [2.9, 15.0], [3.0, 15.0], [3.1, 15.0], [3.2, 15.0], [3.3, 15.0], [3.4, 15.0], [3.5, 15.0], [3.6, 15.0], [3.7, 15.0], [3.8, 15.0], [3.9, 15.0], [4.0, 15.0], [4.1, 15.0], [4.2, 15.0], [4.3, 15.0], [4.4, 15.0], [4.5, 15.0], [4.6, 15.0], [4.7, 15.0], [4.8, 15.0], [4.9, 15.0], [5.0, 15.0], [5.1, 15.0], [5.2, 15.0], [5.3, 15.0], [5.4, 15.0], [5.5, 15.0], [5.6, 15.0], [5.7, 15.0], [5.8, 15.0], [5.9, 15.0], [6.0, 15.0], [6.1, 15.0], [6.2, 15.0], [6.3, 15.0], [6.4, 15.0], [6.5, 15.0], [6.6, 15.0], [6.7, 15.0], [6.8, 15.0], [6.9, 15.0], [7.0, 15.0], [7.1, 15.0], [7.2, 15.0], [7.3, 15.0], [7.4, 15.0], [7.5, 15.0], [7.6, 15.0], [7.7, 15.0], [7.8, 15.0], [7.9, 15.0], [8.0, 15.0], [8.1, 15.0], [8.2, 15.0], [8.3, 15.0], [8.4, 15.0], [8.5, 15.0], [8.6, 15.0], [8.7, 15.0], [8.8, 15.0], [8.9, 15.0], [9.0, 15.0], [9.1, 15.0], [9.2, 15.0], [9.3, 15.0], [9.4, 15.0], [9.5, 15.0], [9.6, 15.0], [9.7, 15.0], [9.8, 15.0], [9.9, 15.0], [10.0, 15.0], [10.1, 15.0], [10.2, 15.0], [10.3, 15.0], [10.4, 15.0], [10.5, 15.0], [10.6, 15.0], [10.7, 15.0], [10.8, 15.0], [10.9, 15.0], [11.0, 15.0], [11.1, 15.0], [11.2, 15.0], [11.3, 15.0], [11.4, 15.0], [11.5, 15.0], [11.6, 15.0], [11.7, 15.0], [11.8, 15.0], [11.9, 15.0], [12.0, 15.0], [12.1, 15.0], [12.2, 15.0], [12.3, 15.0], [12.4, 15.0], [12.5, 15.0], [12.6, 15.0], [12.7, 15.0], [12.8, 15.0], [12.9, 15.0], [13.0, 15.0], [13.1, 15.0], [13.2, 15.0], [13.3, 15.0], [13.4, 15.0], [13.5, 15.0], [13.6, 15.0], [13.7, 15.0], [13.8, 15.0], [13.9, 15.0], [14.0, 15.0], [14.1, 15.0], [14.2, 15.0], [14.3, 15.0], [14.4, 15.0], [14.5, 15.0], [14.6, 15.0], [14.7, 15.0], [14.8, 15.0], [14.9, 15.0], [15.0, 15.0], [15.1, 15.0], [15.2, 15.0], [15.3, 16.0], [15.4, 16.0], [15.5, 16.0], [15.6, 16.0], [15.7, 16.0], [15.8, 16.0], [15.9, 16.0], [16.0, 16.0], [16.1, 16.0], [16.2, 16.0], [16.3, 16.0], [16.4, 16.0], [16.5, 16.0], [16.6, 16.0], [16.7, 16.0], [16.8, 16.0], [16.9, 16.0], [17.0, 16.0], [17.1, 16.0], [17.2, 16.0], [17.3, 16.0], [17.4, 16.0], [17.5, 16.0], [17.6, 16.0], [17.7, 16.0], [17.8, 16.0], [17.9, 16.0], [18.0, 16.0], [18.1, 16.0], [18.2, 16.0], [18.3, 16.0], [18.4, 16.0], [18.5, 16.0], [18.6, 16.0], [18.7, 16.0], [18.8, 16.0], [18.9, 16.0], [19.0, 16.0], [19.1, 16.0], [19.2, 16.0], [19.3, 16.0], [19.4, 16.0], [19.5, 16.0], [19.6, 16.0], [19.7, 16.0], [19.8, 16.0], [19.9, 16.0], [20.0, 16.0], [20.1, 16.0], [20.2, 16.0], [20.3, 16.0], [20.4, 16.0], [20.5, 16.0], [20.6, 16.0], [20.7, 16.0], [20.8, 16.0], [20.9, 16.0], [21.0, 16.0], [21.1, 16.0], [21.2, 16.0], [21.3, 16.0], [21.4, 16.0], [21.5, 16.0], [21.6, 16.0], [21.7, 16.0], [21.8, 16.0], [21.9, 16.0], [22.0, 16.0], [22.1, 16.0], [22.2, 16.0], [22.3, 16.0], [22.4, 16.0], [22.5, 16.0], [22.6, 16.0], [22.7, 16.0], [22.8, 16.0], [22.9, 16.0], [23.0, 16.0], [23.1, 16.0], [23.2, 16.0], [23.3, 16.0], [23.4, 16.0], [23.5, 16.0], [23.6, 16.0], [23.7, 16.0], [23.8, 16.0], [23.9, 16.0], [24.0, 16.0], [24.1, 16.0], [24.2, 16.0], [24.3, 16.0], [24.4, 16.0], [24.5, 16.0], [24.6, 16.0], [24.7, 16.0], [24.8, 16.0], [24.9, 16.0], [25.0, 16.0], [25.1, 16.0], [25.2, 16.0], [25.3, 16.0], [25.4, 16.0], [25.5, 16.0], [25.6, 16.0], [25.7, 16.0], [25.8, 16.0], [25.9, 16.0], [26.0, 16.0], [26.1, 16.0], [26.2, 16.0], [26.3, 16.0], [26.4, 16.0], [26.5, 16.0], [26.6, 16.0], [26.7, 16.0], [26.8, 16.0], [26.9, 16.0], [27.0, 16.0], [27.1, 16.0], [27.2, 16.0], [27.3, 16.0], [27.4, 16.0], [27.5, 16.0], [27.6, 16.0], [27.7, 16.0], [27.8, 16.0], [27.9, 16.0], [28.0, 16.0], [28.1, 16.0], [28.2, 16.0], [28.3, 16.0], [28.4, 16.0], [28.5, 16.0], [28.6, 16.0], [28.7, 16.0], [28.8, 16.0], [28.9, 16.0], [29.0, 16.0], [29.1, 16.0], [29.2, 16.0], [29.3, 16.0], [29.4, 16.0], [29.5, 16.0], [29.6, 16.0], [29.7, 16.0], [29.8, 16.0], [29.9, 16.0], [30.0, 16.0], [30.1, 16.0], [30.2, 16.0], [30.3, 16.0], [30.4, 16.0], [30.5, 16.0], [30.6, 16.0], [30.7, 16.0], [30.8, 16.0], [30.9, 16.0], [31.0, 16.0], [31.1, 16.0], [31.2, 16.0], [31.3, 16.0], [31.4, 16.0], [31.5, 16.0], [31.6, 16.0], [31.7, 16.0], [31.8, 16.0], [31.9, 16.0], [32.0, 16.0], [32.1, 16.0], [32.2, 16.0], [32.3, 16.0], [32.4, 16.0], [32.5, 16.0], [32.6, 16.0], [32.7, 16.0], [32.8, 16.0], [32.9, 16.0], [33.0, 16.0], [33.1, 16.0], [33.2, 16.0], [33.3, 16.0], [33.4, 16.0], [33.5, 16.0], [33.6, 16.0], [33.7, 16.0], [33.8, 16.0], [33.9, 16.0], [34.0, 16.0], [34.1, 16.0], [34.2, 16.0], [34.3, 16.0], [34.4, 16.0], [34.5, 16.0], [34.6, 16.0], [34.7, 16.0], [34.8, 16.0], [34.9, 16.0], [35.0, 16.0], [35.1, 16.0], [35.2, 16.0], [35.3, 16.0], [35.4, 16.0], [35.5, 16.0], [35.6, 16.0], [35.7, 16.0], [35.8, 16.0], [35.9, 16.0], [36.0, 16.0], [36.1, 16.0], [36.2, 16.0], [36.3, 16.0], [36.4, 16.0], [36.5, 16.0], [36.6, 16.0], [36.7, 16.0], [36.8, 16.0], [36.9, 16.0], [37.0, 16.0], [37.1, 16.0], [37.2, 16.0], [37.3, 16.0], [37.4, 16.0], [37.5, 16.0], [37.6, 16.0], [37.7, 16.0], [37.8, 16.0], [37.9, 16.0], [38.0, 16.0], [38.1, 16.0], [38.2, 16.0], [38.3, 16.0], [38.4, 16.0], [38.5, 16.0], [38.6, 16.0], [38.7, 16.0], [38.8, 16.0], [38.9, 16.0], [39.0, 16.0], [39.1, 16.0], [39.2, 16.0], [39.3, 16.0], [39.4, 16.0], [39.5, 16.0], [39.6, 16.0], [39.7, 16.0], [39.8, 16.0], [39.9, 16.0], [40.0, 16.0], [40.1, 16.0], [40.2, 17.0], [40.3, 17.0], [40.4, 17.0], [40.5, 17.0], [40.6, 17.0], [40.7, 17.0], [40.8, 17.0], [40.9, 17.0], [41.0, 17.0], [41.1, 17.0], [41.2, 17.0], [41.3, 17.0], [41.4, 17.0], [41.5, 17.0], [41.6, 17.0], [41.7, 17.0], [41.8, 17.0], [41.9, 17.0], [42.0, 17.0], [42.1, 17.0], [42.2, 17.0], [42.3, 17.0], [42.4, 17.0], [42.5, 17.0], [42.6, 17.0], [42.7, 17.0], [42.8, 17.0], [42.9, 17.0], [43.0, 17.0], [43.1, 17.0], [43.2, 17.0], [43.3, 17.0], [43.4, 17.0], [43.5, 17.0], [43.6, 17.0], [43.7, 17.0], [43.8, 17.0], [43.9, 17.0], [44.0, 17.0], [44.1, 17.0], [44.2, 17.0], [44.3, 17.0], [44.4, 17.0], [44.5, 17.0], [44.6, 17.0], [44.7, 17.0], [44.8, 17.0], [44.9, 17.0], [45.0, 17.0], [45.1, 17.0], [45.2, 17.0], [45.3, 17.0], [45.4, 17.0], [45.5, 17.0], [45.6, 17.0], [45.7, 17.0], [45.8, 17.0], [45.9, 17.0], [46.0, 17.0], [46.1, 17.0], [46.2, 17.0], [46.3, 17.0], [46.4, 17.0], [46.5, 17.0], [46.6, 17.0], [46.7, 17.0], [46.8, 17.0], [46.9, 17.0], [47.0, 17.0], [47.1, 17.0], [47.2, 17.0], [47.3, 17.0], [47.4, 17.0], [47.5, 17.0], [47.6, 17.0], [47.7, 17.0], [47.8, 17.0], [47.9, 17.0], [48.0, 17.0], [48.1, 17.0], [48.2, 17.0], [48.3, 17.0], [48.4, 17.0], [48.5, 17.0], [48.6, 17.0], [48.7, 17.0], [48.8, 17.0], [48.9, 17.0], [49.0, 17.0], [49.1, 17.0], [49.2, 17.0], [49.3, 17.0], [49.4, 17.0], [49.5, 17.0], [49.6, 17.0], [49.7, 17.0], [49.8, 17.0], [49.9, 17.0], [50.0, 17.0], [50.1, 17.0], [50.2, 17.0], [50.3, 17.0], [50.4, 17.0], [50.5, 17.0], [50.6, 17.0], [50.7, 17.0], [50.8, 17.0], [50.9, 17.0], [51.0, 17.0], [51.1, 17.0], [51.2, 17.0], [51.3, 17.0], [51.4, 17.0], [51.5, 17.0], [51.6, 17.0], [51.7, 17.0], [51.8, 17.0], [51.9, 17.0], [52.0, 17.0], [52.1, 17.0], [52.2, 17.0], [52.3, 17.0], [52.4, 17.0], [52.5, 17.0], [52.6, 17.0], [52.7, 17.0], [52.8, 17.0], [52.9, 17.0], [53.0, 17.0], [53.1, 17.0], [53.2, 17.0], [53.3, 17.0], [53.4, 17.0], [53.5, 17.0], [53.6, 17.0], [53.7, 17.0], [53.8, 17.0], [53.9, 17.0], [54.0, 17.0], [54.1, 17.0], [54.2, 17.0], [54.3, 17.0], [54.4, 17.0], [54.5, 17.0], [54.6, 17.0], [54.7, 17.0], [54.8, 17.0], [54.9, 17.0], [55.0, 17.0], [55.1, 17.0], [55.2, 17.0], [55.3, 17.0], [55.4, 17.0], [55.5, 17.0], [55.6, 17.0], [55.7, 17.0], [55.8, 17.0], [55.9, 17.0], [56.0, 17.0], [56.1, 17.0], [56.2, 17.0], [56.3, 17.0], [56.4, 17.0], [56.5, 17.0], [56.6, 17.0], [56.7, 17.0], [56.8, 17.0], [56.9, 17.0], [57.0, 17.0], [57.1, 17.0], [57.2, 17.0], [57.3, 17.0], [57.4, 17.0], [57.5, 17.0], [57.6, 17.0], [57.7, 17.0], [57.8, 17.0], [57.9, 17.0], [58.0, 17.0], [58.1, 17.0], [58.2, 17.0], [58.3, 17.0], [58.4, 17.0], [58.5, 17.0], [58.6, 17.0], [58.7, 18.0], [58.8, 18.0], [58.9, 18.0], [59.0, 18.0], [59.1, 18.0], [59.2, 18.0], [59.3, 18.0], [59.4, 18.0], [59.5, 18.0], [59.6, 18.0], [59.7, 18.0], [59.8, 18.0], [59.9, 18.0], [60.0, 18.0], [60.1, 18.0], [60.2, 18.0], [60.3, 18.0], [60.4, 18.0], [60.5, 18.0], [60.6, 18.0], [60.7, 18.0], [60.8, 18.0], [60.9, 18.0], [61.0, 18.0], [61.1, 18.0], [61.2, 18.0], [61.3, 18.0], [61.4, 18.0], [61.5, 18.0], [61.6, 18.0], [61.7, 18.0], [61.8, 18.0], [61.9, 18.0], [62.0, 18.0], [62.1, 18.0], [62.2, 18.0], [62.3, 18.0], [62.4, 18.0], [62.5, 18.0], [62.6, 18.0], [62.7, 18.0], [62.8, 18.0], [62.9, 18.0], [63.0, 18.0], [63.1, 18.0], [63.2, 18.0], [63.3, 18.0], [63.4, 18.0], [63.5, 18.0], [63.6, 18.0], [63.7, 18.0], [63.8, 18.0], [63.9, 18.0], [64.0, 18.0], [64.1, 18.0], [64.2, 18.0], [64.3, 18.0], [64.4, 18.0], [64.5, 18.0], [64.6, 18.0], [64.7, 18.0], [64.8, 18.0], [64.9, 18.0], [65.0, 18.0], [65.1, 18.0], [65.2, 18.0], [65.3, 18.0], [65.4, 18.0], [65.5, 18.0], [65.6, 18.0], [65.7, 18.0], [65.8, 18.0], [65.9, 18.0], [66.0, 18.0], [66.1, 18.0], [66.2, 18.0], [66.3, 18.0], [66.4, 18.0], [66.5, 18.0], [66.6, 18.0], [66.7, 18.0], [66.8, 18.0], [66.9, 18.0], [67.0, 18.0], [67.1, 18.0], [67.2, 18.0], [67.3, 18.0], [67.4, 18.0], [67.5, 18.0], [67.6, 18.0], [67.7, 18.0], [67.8, 18.0], [67.9, 18.0], [68.0, 18.0], [68.1, 18.0], [68.2, 18.0], [68.3, 18.0], [68.4, 18.0], [68.5, 18.0], [68.6, 18.0], [68.7, 18.0], [68.8, 18.0], [68.9, 19.0], [69.0, 19.0], [69.1, 19.0], [69.2, 19.0], [69.3, 19.0], [69.4, 19.0], [69.5, 19.0], [69.6, 19.0], [69.7, 19.0], [69.8, 19.0], [69.9, 19.0], [70.0, 19.0], [70.1, 19.0], [70.2, 19.0], [70.3, 19.0], [70.4, 19.0], [70.5, 19.0], [70.6, 19.0], [70.7, 19.0], [70.8, 19.0], [70.9, 19.0], [71.0, 19.0], [71.1, 19.0], [71.2, 19.0], [71.3, 19.0], [71.4, 19.0], [71.5, 19.0], [71.6, 19.0], [71.7, 19.0], [71.8, 19.0], [71.9, 19.0], [72.0, 19.0], [72.1, 19.0], [72.2, 19.0], [72.3, 19.0], [72.4, 19.0], [72.5, 19.0], [72.6, 19.0], [72.7, 19.0], [72.8, 19.0], [72.9, 19.0], [73.0, 19.0], [73.1, 19.0], [73.2, 19.0], [73.3, 19.0], [73.4, 19.0], [73.5, 19.0], [73.6, 19.0], [73.7, 19.0], [73.8, 19.0], [73.9, 19.0], [74.0, 19.0], [74.1, 19.0], [74.2, 19.0], [74.3, 19.0], [74.4, 19.0], [74.5, 19.0], [74.6, 19.0], [74.7, 19.0], [74.8, 19.0], [74.9, 19.0], [75.0, 19.0], [75.1, 19.0], [75.2, 19.0], [75.3, 19.0], [75.4, 19.0], [75.5, 19.0], [75.6, 19.0], [75.7, 19.0], [75.8, 19.0], [75.9, 19.0], [76.0, 19.0], [76.1, 20.0], [76.2, 20.0], [76.3, 20.0], [76.4, 20.0], [76.5, 20.0], [76.6, 20.0], [76.7, 20.0], [76.8, 20.0], [76.9, 20.0], [77.0, 20.0], [77.1, 20.0], [77.2, 20.0], [77.3, 20.0], [77.4, 20.0], [77.5, 20.0], [77.6, 20.0], [77.7, 20.0], [77.8, 20.0], [77.9, 20.0], [78.0, 20.0], [78.1, 20.0], [78.2, 20.0], [78.3, 20.0], [78.4, 20.0], [78.5, 20.0], [78.6, 20.0], [78.7, 20.0], [78.8, 20.0], [78.9, 20.0], [79.0, 20.0], [79.1, 20.0], [79.2, 20.0], [79.3, 20.0], [79.4, 21.0], [79.5, 21.0], [79.6, 21.0], [79.7, 21.0], [79.8, 21.0], [79.9, 21.0], [80.0, 21.0], [80.1, 21.0], [80.2, 21.0], [80.3, 21.0], [80.4, 21.0], [80.5, 21.0], [80.6, 21.0], [80.7, 21.0], [80.8, 21.0], [80.9, 21.0], [81.0, 21.0], [81.1, 21.0], [81.2, 21.0], [81.3, 21.0], [81.4, 21.0], [81.5, 21.0], [81.6, 21.0], [81.7, 21.0], [81.8, 21.0], [81.9, 21.0], [82.0, 21.0], [82.1, 21.0], [82.2, 21.0], [82.3, 21.0], [82.4, 22.0], [82.5, 22.0], [82.6, 22.0], [82.7, 22.0], [82.8, 22.0], [82.9, 22.0], [83.0, 22.0], [83.1, 22.0], [83.2, 22.0], [83.3, 22.0], [83.4, 22.0], [83.5, 22.0], [83.6, 22.0], [83.7, 22.0], [83.8, 23.0], [83.9, 23.0], [84.0, 23.0], [84.1, 23.0], [84.2, 23.0], [84.3, 23.0], [84.4, 23.0], [84.5, 23.0], [84.6, 23.0], [84.7, 23.0], [84.8, 23.0], [84.9, 23.0], [85.0, 23.0], [85.1, 23.0], [85.2, 23.0], [85.3, 24.0], [85.4, 24.0], [85.5, 24.0], [85.6, 24.0], [85.7, 24.0], [85.8, 24.0], [85.9, 24.0], [86.0, 24.0], [86.1, 24.0], [86.2, 24.0], [86.3, 24.0], [86.4, 24.0], [86.5, 24.0], [86.6, 24.0], [86.7, 24.0], [86.8, 24.0], [86.9, 24.0], [87.0, 24.0], [87.1, 24.0], [87.2, 24.0], [87.3, 25.0], [87.4, 25.0], [87.5, 25.0], [87.6, 25.0], [87.7, 25.0], [87.8, 25.0], [87.9, 25.0], [88.0, 25.0], [88.1, 25.0], [88.2, 25.0], [88.3, 25.0], [88.4, 25.0], [88.5, 25.0], [88.6, 25.0], [88.7, 25.0], [88.8, 25.0], [88.9, 25.0], [89.0, 25.0], [89.1, 25.0], [89.2, 25.0], [89.3, 25.0], [89.4, 25.0], [89.5, 25.0], [89.6, 26.0], [89.7, 26.0], [89.8, 26.0], [89.9, 26.0], [90.0, 26.0], [90.1, 26.0], [90.2, 26.0], [90.3, 26.0], [90.4, 26.0], [90.5, 26.0], [90.6, 26.0], [90.7, 26.0], [90.8, 27.0], [90.9, 27.0], [91.0, 27.0], [91.1, 27.0], [91.2, 27.0], [91.3, 27.0], [91.4, 28.0], [91.5, 28.0], [91.6, 28.0], [91.7, 28.0], [91.8, 28.0], [91.9, 28.0], [92.0, 28.0], [92.1, 28.0], [92.2, 28.0], [92.3, 29.0], [92.4, 29.0], [92.5, 29.0], [92.6, 29.0], [92.7, 30.0], [92.8, 30.0], [92.9, 31.0], [93.0, 31.0], [93.1, 32.0], [93.2, 32.0], [93.3, 32.0], [93.4, 32.0], [93.5, 32.0], [93.6, 32.0], [93.7, 33.0], [93.8, 33.0], [93.9, 33.0], [94.0, 33.0], [94.1, 33.0], [94.2, 33.0], [94.3, 34.0], [94.4, 34.0], [94.5, 34.0], [94.6, 34.0], [94.7, 34.0], [94.8, 35.0], [94.9, 35.0], [95.0, 35.0], [95.1, 36.0], [95.2, 36.0], [95.3, 36.0], [95.4, 37.0], [95.5, 38.0], [95.6, 39.0], [95.7, 39.0], [95.8, 39.0], [95.9, 40.0], [96.0, 41.0], [96.1, 42.0], [96.2, 43.0], [96.3, 43.0], [96.4, 44.0], [96.5, 44.0], [96.6, 44.0], [96.7, 45.0], [96.8, 48.0], [96.9, 50.0], [97.0, 55.0], [97.1, 57.0], [97.2, 58.0], [97.3, 59.0], [97.4, 60.0], [97.5, 63.0], [97.6, 64.0], [97.7, 65.0], [97.8, 67.0], [97.9, 69.0], [98.0, 70.0], [98.1, 72.0], [98.2, 74.0], [98.3, 76.0], [98.4, 77.0], [98.5, 79.0], [98.6, 80.0], [98.7, 87.0], [98.8, 89.0], [98.9, 90.0], [99.0, 93.0], [99.1, 97.0], [99.2, 104.0], [99.3, 113.0], [99.4, 121.0], [99.5, 131.0], [99.6, 133.0], [99.7, 147.0], [99.8, 577.0], [99.9, 1168.0]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "maxX": 100.0, "title": "Response Time Percentiles"}},
        getOptions: function() {
            return {
                series: {
                    points: { show: false }
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimePercentiles'
                },
                xaxis: {
                    tickDecimals: 1,
                    axisLabel: "Percentiles",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Percentile value in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : %x.2 percentile was %y ms"
                },
                selection: { mode: "xy" },
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesResponseTimePercentiles"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimesPercentiles"), dataset, options);
            // setup overview
            $.plot($("#overviewResponseTimesPercentiles"), dataset, prepareOverviewOptions(options));
        }
};

/**
 * @param elementId Id of element where we display message
 */
function setEmptyGraph(elementId) {
    $(function() {
        $(elementId).text("No graph series with filter="+seriesFilter);
    });
}

// Response times percentiles
function refreshResponseTimePercentiles() {
    var infos = responseTimePercentilesInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyResponseTimePercentiles");
        return;
    }
    if (isGraph($("#flotResponseTimesPercentiles"))){
        infos.createGraph();
    } else {
        var choiceContainer = $("#choicesResponseTimePercentiles");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimesPercentiles", "#overviewResponseTimesPercentiles");
        $('#bodyResponseTimePercentiles .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
}

var responseTimeDistributionInfos = {
        data: {"result": {"minY": 1.0, "minX": 0.0, "maxY": 1983.0, "series": [{"data": [[0.0, 1983.0], [1100.0, 1.0], [1300.0, 1.0], [200.0, 1.0], [800.0, 1.0], [100.0, 12.0], [500.0, 1.0]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 100, "maxX": 1300.0, "title": "Response Time Distribution"}},
        getOptions: function() {
            var granularity = this.data.result.granularity;
            return {
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimeDistribution'
                },
                xaxis:{
                    axisLabel: "Response times in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of responses",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                bars : {
                    show: true,
                    barWidth: this.data.result.granularity
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: function(label, xval, yval, flotItem){
                        return yval + " responses for " + label + " were between " + xval + " and " + (xval + granularity) + " ms";
                    }
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimeDistribution"), prepareData(data.result.series, $("#choicesResponseTimeDistribution")), options);
        }

};

// Response time distribution
function refreshResponseTimeDistribution() {
    var infos = responseTimeDistributionInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyResponseTimeDistribution");
        return;
    }
    if (isGraph($("#flotResponseTimeDistribution"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesResponseTimeDistribution");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        $('#footerResponseTimeDistribution .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};


var syntheticResponseTimeDistributionInfos = {
        data: {"result": {"minY": 4.0, "minX": 0.0, "ticks": [[0, "Requests having \nresponse time <= 500ms"], [1, "Requests having \nresponse time > 500ms and <= 1,500ms"], [2, "Requests having \nresponse time > 1,500ms"], [3, "Requests in error"]], "maxY": 1996.0, "series": [{"data": [[0.0, 1996.0]], "color": "#9ACD32", "isOverall": false, "label": "Requests having \nresponse time <= 500ms", "isController": false}, {"data": [[1.0, 4.0]], "color": "yellow", "isOverall": false, "label": "Requests having \nresponse time > 500ms and <= 1,500ms", "isController": false}, {"data": [], "color": "orange", "isOverall": false, "label": "Requests having \nresponse time > 1,500ms", "isController": false}, {"data": [], "color": "#FF6347", "isOverall": false, "label": "Requests in error", "isController": false}], "supportsControllersDiscrimination": false, "maxX": 1.0, "title": "Synthetic Response Times Distribution"}},
        getOptions: function() {
            return {
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendSyntheticResponseTimeDistribution'
                },
                xaxis:{
                    axisLabel: "Response times ranges",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                    tickLength:0,
                    min:-0.5,
                    max:3.5
                },
                yaxis: {
                    axisLabel: "Number of responses",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                bars : {
                    show: true,
                    align: "center",
                    barWidth: 0.25,
                    fill:.75
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: function(label, xval, yval, flotItem){
                        return yval + " " + label;
                    }
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var options = this.getOptions();
            prepareOptions(options, data);
            options.xaxis.ticks = data.result.ticks;
            $.plot($("#flotSyntheticResponseTimeDistribution"), prepareData(data.result.series, $("#choicesSyntheticResponseTimeDistribution")), options);
        }

};

// Response time distribution
function refreshSyntheticResponseTimeDistribution() {
    var infos = syntheticResponseTimeDistributionInfos;
    prepareSeries(infos.data, true);
    if (isGraph($("#flotSyntheticResponseTimeDistribution"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesSyntheticResponseTimeDistribution");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        $('#footerSyntheticResponseTimeDistribution .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var activeThreadsOverTimeInfos = {
        data: {"result": {"minY": 1.0, "minX": 1.7317539E12, "maxY": 5.722222222222222, "series": [{"data": [[1.731753909E12, 1.0], [1.731753952E12, 1.0], [1.731753907E12, 1.0], [1.73175395E12, 1.0], [1.731753905E12, 1.0], [1.731753948E12, 1.0], [1.731753903E12, 1.0], [1.731753946E12, 1.0], [1.731753901E12, 5.04054054054054], [1.731753944E12, 1.0], [1.731753942E12, 1.0], [1.731753919E12, 1.0], [1.731753917E12, 1.0], [1.731753915E12, 1.0], [1.731753958E12, 1.0], [1.731753913E12, 1.0], [1.731753956E12, 1.0], [1.731753911E12, 1.0], [1.731753954E12, 1.0], [1.731753929E12, 1.0], [1.731753927E12, 1.0], [1.731753925E12, 1.0], [1.731753923E12, 1.0], [1.731753921E12, 1.0], [1.731753941E12, 1.0], [1.731753939E12, 1.0], [1.731753937E12, 1.0], [1.731753935E12, 1.0], [1.731753933E12, 1.0], [1.731753931E12, 1.0], [1.731753951E12, 1.0], [1.731753908E12, 1.0], [1.731753949E12, 1.0], [1.731753906E12, 1.0], [1.731753947E12, 1.0], [1.731753904E12, 1.0], [1.731753945E12, 1.0], [1.731753902E12, 1.0], [1.731753943E12, 1.0], [1.7317539E12, 5.722222222222222], [1.73175392E12, 1.0], [1.731753918E12, 1.0], [1.731753959E12, 1.0], [1.731753916E12, 1.0], [1.731753957E12, 1.0], [1.731753914E12, 1.0], [1.731753955E12, 1.0], [1.731753912E12, 1.0], [1.731753953E12, 1.0], [1.73175391E12, 1.0], [1.73175393E12, 1.0], [1.731753928E12, 1.0], [1.731753926E12, 1.0], [1.731753924E12, 1.0], [1.731753922E12, 1.0], [1.73175394E12, 1.0], [1.731753938E12, 1.0], [1.731753936E12, 1.0], [1.731753934E12, 1.0], [1.731753932E12, 1.0]], "isOverall": false, "label": "线程组", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731753959E12, "title": "Active Threads Over Time"}},
        getOptions: function() {
            return {
                series: {
                    stack: true,
                    lines: {
                        show: true,
                        fill: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of active threads",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 6,
                    show: true,
                    container: '#legendActiveThreadsOverTime'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                selection: {
                    mode: 'xy'
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : At %x there were %y active threads"
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesActiveThreadsOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotActiveThreadsOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewActiveThreadsOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Active Threads Over Time
function refreshActiveThreadsOverTime(fixTimestamps) {
    var infos = activeThreadsOverTimeInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotActiveThreadsOverTime"))) {
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesActiveThreadsOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotActiveThreadsOverTime", "#overviewActiveThreadsOverTime");
        $('#footerActiveThreadsOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var timeVsThreadsInfos = {
        data: {"result": {"minY": 18.384856396866834, "minX": 1.0, "maxY": 718.5, "series": [{"data": [[8.0, 68.66666666666666], [4.0, 66.0], [2.0, 37.76470588235295], [1.0, 18.384856396866834], [5.0, 718.5], [6.0, 77.92], [3.0, 135.0], [7.0, 75.39285714285714]], "isOverall": false, "label": "Products", "isController": false}, {"data": [[1.1920000000000006, 22.449000000000012]], "isOverall": false, "label": "Products-Aggregated", "isController": false}], "supportsControllersDiscrimination": true, "maxX": 8.0, "title": "Time VS Threads"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    axisLabel: "Number of active threads",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average response times in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: { noColumns: 2,show: true, container: '#legendTimeVsThreads' },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s: At %x.2 active threads, Average response time was %y.2 ms"
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesTimeVsThreads"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotTimesVsThreads"), dataset, options);
            // setup overview
            $.plot($("#overviewTimesVsThreads"), dataset, prepareOverviewOptions(options));
        }
};

// Time vs threads
function refreshTimeVsThreads(){
    var infos = timeVsThreadsInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyTimeVsThreads");
        return;
    }
    if(isGraph($("#flotTimesVsThreads"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesTimeVsThreads");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotTimesVsThreads", "#overviewTimesVsThreads");
        $('#footerTimeVsThreads .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var bytesThroughputOverTimeInfos = {
        data : {"result": {"minY": 1205.0, "minX": 1.7317539E12, "maxY": 156611.0, "series": [{"data": [[1.731753909E12, 62781.0], [1.731753952E12, 66494.0], [1.731753907E12, 64474.0], [1.73175395E12, 65393.0], [1.731753905E12, 62577.0], [1.731753948E12, 51641.0], [1.731753903E12, 55655.0], [1.731753946E12, 87732.0], [1.731753901E12, 156611.0], [1.731753944E12, 66988.0], [1.731753942E12, 48334.0], [1.731753919E12, 68969.0], [1.731753917E12, 57660.0], [1.731753915E12, 53609.0], [1.731753958E12, 67487.0], [1.731753913E12, 67290.0], [1.731753956E12, 64579.0], [1.731753911E12, 68986.0], [1.731753954E12, 59056.0], [1.731753929E12, 66336.0], [1.731753927E12, 46131.0], [1.731753925E12, 71276.0], [1.731753923E12, 64104.0], [1.731753921E12, 54823.0], [1.731753941E12, 64125.0], [1.731753939E12, 59624.0], [1.731753937E12, 65717.0], [1.731753935E12, 64440.0], [1.731753933E12, 52274.0], [1.731753931E12, 87446.0], [1.731753951E12, 55184.0], [1.731753908E12, 62702.0], [1.731753949E12, 67392.0], [1.731753906E12, 58606.0], [1.731753947E12, 60179.0], [1.731753904E12, 66850.0], [1.731753945E12, 54372.0], [1.731753902E12, 61422.0], [1.731753943E12, 67605.0], [1.7317539E12, 31193.0], [1.73175392E12, 64785.0], [1.731753918E12, 53536.0], [1.731753959E12, 10662.0], [1.731753916E12, 88532.0], [1.731753957E12, 48478.0], [1.731753914E12, 68209.0], [1.731753955E12, 72951.0], [1.731753912E12, 46292.0], [1.731753953E12, 63020.0], [1.73175391E12, 68119.0], [1.73175393E12, 53780.0], [1.731753928E12, 68717.0], [1.731753926E12, 66292.0], [1.731753924E12, 59650.0], [1.731753922E12, 66049.0], [1.73175394E12, 71276.0], [1.731753938E12, 64910.0], [1.731753936E12, 55155.0], [1.731753934E12, 68368.0], [1.731753932E12, 60448.0]], "isOverall": false, "label": "Bytes received per second", "isController": false}, {"data": [[1.731753909E12, 7908.0], [1.731753952E12, 8622.0], [1.731753907E12, 8368.0], [1.73175395E12, 8821.0], [1.731753905E12, 8294.0], [1.731753948E12, 7181.0], [1.731753903E12, 7696.0], [1.731753946E12, 8574.0], [1.731753901E12, 18079.0], [1.731753944E12, 8722.0], [1.731753942E12, 8005.0], [1.731753919E12, 8731.0], [1.731753917E12, 8339.0], [1.731753915E12, 7324.0], [1.731753958E12, 8695.0], [1.731753913E12, 8415.0], [1.731753956E12, 8045.0], [1.731753911E12, 8854.0], [1.731753954E12, 7392.0], [1.731753929E12, 8714.0], [1.731753927E12, 7734.0], [1.731753925E12, 8540.0], [1.731753923E12, 8682.0], [1.731753921E12, 7521.0], [1.731753941E12, 8068.0], [1.731753939E12, 7392.0], [1.731753937E12, 8603.0], [1.731753935E12, 8565.0], [1.731753933E12, 7217.0], [1.731753931E12, 8583.0], [1.731753951E12, 7549.0], [1.731753908E12, 8429.0], [1.731753949E12, 8466.0], [1.731753906E12, 8022.0], [1.731753947E12, 8620.0], [1.731753904E12, 8496.0], [1.731753945E12, 7253.0], [1.731753902E12, 8855.0], [1.731753943E12, 8695.0], [1.7317539E12, 4515.0], [1.73175392E12, 8542.0], [1.731753918E12, 7461.0], [1.731753959E12, 1205.0], [1.731753916E12, 8566.0], [1.731753957E12, 8050.0], [1.731753914E12, 8940.0], [1.731753955E12, 8554.0], [1.731753912E12, 7734.0], [1.731753953E12, 8657.0], [1.73175391E12, 8042.0], [1.73175393E12, 7288.0], [1.731753928E12, 8677.0], [1.731753926E12, 8342.0], [1.731753924E12, 7407.0], [1.731753922E12, 8621.0], [1.73175394E12, 8558.0], [1.731753938E12, 8682.0], [1.731753936E12, 7534.0], [1.731753934E12, 8704.0], [1.731753932E12, 8584.0]], "isOverall": false, "label": "Bytes sent per second", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731753959E12, "title": "Bytes Throughput Over Time"}},
        getOptions : function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity) ,
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Bytes / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendBytesThroughputOverTime'
                },
                selection: {
                    mode: "xy"
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y"
                }
            };
        },
        createGraph : function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesBytesThroughputOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotBytesThroughputOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewBytesThroughputOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Bytes throughput Over Time
function refreshBytesThroughputOverTime(fixTimestamps) {
    var infos = bytesThroughputOverTimeInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotBytesThroughputOverTime"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesBytesThroughputOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotBytesThroughputOverTime", "#overviewBytesThroughputOverTime");
        $('#footerBytesThroughputOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
}

var responseTimesOverTimeInfos = {
        data: {"result": {"minY": 14.6, "minX": 1.7317539E12, "maxY": 298.1111111111112, "series": [{"data": [[1.731753909E12, 20.718749999999993], [1.731753952E12, 17.71428571428571], [1.731753907E12, 21.97058823529412], [1.73175395E12, 16.499999999999996], [1.731753905E12, 20.029411764705884], [1.731753948E12, 17.033333333333335], [1.731753903E12, 22.937499999999996], [1.731753946E12, 19.771428571428572], [1.731753901E12, 60.621621621621586], [1.731753944E12, 17.82857142857143], [1.731753942E12, 15.906250000000004], [1.731753919E12, 18.485714285714284], [1.731753917E12, 18.794117647058822], [1.731753915E12, 18.566666666666666], [1.731753958E12, 16.599999999999994], [1.731753913E12, 18.647058823529413], [1.731753956E12, 17.66666666666667], [1.731753911E12, 19.499999999999996], [1.731753954E12, 17.800000000000008], [1.731753929E12, 18.057142857142857], [1.731753927E12, 16.48387096774194], [1.731753925E12, 18.8], [1.731753923E12, 17.34285714285714], [1.731753921E12, 16.96666666666667], [1.731753941E12, 18.24242424242424], [1.731753939E12, 17.73333333333333], [1.731753937E12, 17.942857142857147], [1.731753935E12, 16.257142857142863], [1.731753933E12, 17.03333333333333], [1.731753931E12, 21.25714285714286], [1.731753951E12, 15.466666666666667], [1.731753908E12, 19.73529411764705], [1.731753949E12, 18.38235294117647], [1.731753906E12, 19.65625], [1.731753947E12, 16.342857142857138], [1.731753904E12, 22.029411764705884], [1.731753945E12, 17.066666666666666], [1.731753902E12, 24.083333333333336], [1.731753943E12, 17.02857142857143], [1.7317539E12, 298.1111111111112], [1.73175392E12, 17.514285714285723], [1.731753918E12, 18.806451612903224], [1.731753959E12, 14.6], [1.731753916E12, 21.914285714285707], [1.731753957E12, 15.656249999999998], [1.731753914E12, 19.583333333333332], [1.731753955E12, 17.599999999999998], [1.731753912E12, 17.806451612903228], [1.731753953E12, 15.742857142857142], [1.73175391E12, 21.090909090909086], [1.73175393E12, 17.300000000000004], [1.731753928E12, 17.6], [1.731753926E12, 18.705882352941178], [1.731753924E12, 18.966666666666672], [1.731753922E12, 19.599999999999998], [1.73175394E12, 18.085714285714285], [1.731753938E12, 16.485714285714288], [1.731753936E12, 16.033333333333335], [1.731753934E12, 18.142857142857146], [1.731753932E12, 17.057142857142857]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731753959E12, "title": "Response Time Over Time"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average response time in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimesOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Average response time was %y ms"
                }
            };
        },
        createGraph: function() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesResponseTimesOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimesOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewResponseTimesOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Response Times Over Time
function refreshResponseTimeOverTime(fixTimestamps) {
    var infos = responseTimesOverTimeInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyResponseTimeOverTime");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotResponseTimesOverTime"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesResponseTimesOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimesOverTime", "#overviewResponseTimesOverTime");
        $('#footerResponseTimesOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var latenciesOverTimeInfos = {
        data: {"result": {"minY": 14.6, "minX": 1.7317539E12, "maxY": 297.94444444444446, "series": [{"data": [[1.731753909E12, 20.718749999999993], [1.731753952E12, 17.71428571428571], [1.731753907E12, 21.764705882352935], [1.73175395E12, 16.499999999999996], [1.731753905E12, 19.88235294117647], [1.731753948E12, 17.0], [1.731753903E12, 22.781250000000004], [1.731753946E12, 19.771428571428572], [1.731753901E12, 59.98648648648645], [1.731753944E12, 17.77142857142857], [1.731753942E12, 15.781249999999998], [1.731753919E12, 18.45714285714286], [1.731753917E12, 18.735294117647058], [1.731753915E12, 18.566666666666666], [1.731753958E12, 16.571428571428566], [1.731753913E12, 18.558823529411768], [1.731753956E12, 17.636363636363637], [1.731753911E12, 19.47222222222222], [1.731753954E12, 17.800000000000008], [1.731753929E12, 18.057142857142857], [1.731753927E12, 16.451612903225808], [1.731753925E12, 18.742857142857147], [1.731753923E12, 17.28571428571428], [1.731753921E12, 16.96666666666667], [1.731753941E12, 18.21212121212121], [1.731753939E12, 17.633333333333336], [1.731753937E12, 17.91428571428572], [1.731753935E12, 16.200000000000003], [1.731753933E12, 16.966666666666665], [1.731753931E12, 21.199999999999996], [1.731753951E12, 15.433333333333334], [1.731753908E12, 19.70588235294118], [1.731753949E12, 18.38235294117647], [1.731753906E12, 19.65625], [1.731753947E12, 16.314285714285713], [1.731753904E12, 22.0], [1.731753945E12, 17.066666666666666], [1.731753902E12, 24.027777777777786], [1.731753943E12, 17.0], [1.7317539E12, 297.94444444444446], [1.73175392E12, 17.48571428571429], [1.731753918E12, 18.741935483870964], [1.731753959E12, 14.6], [1.731753916E12, 21.914285714285707], [1.731753957E12, 15.53125], [1.731753914E12, 19.444444444444443], [1.731753955E12, 17.599999999999998], [1.731753912E12, 17.580645161290324], [1.731753953E12, 15.742857142857142], [1.73175391E12, 21.090909090909086], [1.73175393E12, 17.233333333333334], [1.731753928E12, 17.54285714285714], [1.731753926E12, 18.67647058823529], [1.731753924E12, 18.900000000000002], [1.731753922E12, 19.514285714285723], [1.73175394E12, 18.02857142857143], [1.731753938E12, 16.485714285714288], [1.731753936E12, 16.033333333333335], [1.731753934E12, 18.142857142857146], [1.731753932E12, 17.057142857142857]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731753959E12, "title": "Latencies Over Time"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average response latencies in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendLatenciesOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Average latency was %y ms"
                }
            };
        },
        createGraph: function () {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesLatenciesOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotLatenciesOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewLatenciesOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Latencies Over Time
function refreshLatenciesOverTime(fixTimestamps) {
    var infos = latenciesOverTimeInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyLatenciesOverTime");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotLatenciesOverTime"))) {
        infos.createGraph();
    }else {
        var choiceContainer = $("#choicesLatenciesOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotLatenciesOverTime", "#overviewLatenciesOverTime");
        $('#footerLatenciesOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var connectTimeOverTimeInfos = {
        data: {"result": {"minY": 0.0, "minX": 1.7317539E12, "maxY": 2.777777777777778, "series": [{"data": [[1.731753909E12, 0.09375000000000003], [1.731753952E12, 0.11428571428571431], [1.731753907E12, 0.11764705882352944], [1.73175395E12, 0.08333333333333334], [1.731753905E12, 0.08823529411764708], [1.731753948E12, 0.10000000000000002], [1.731753903E12, 0.09375000000000003], [1.731753946E12, 0.11428571428571431], [1.731753901E12, 0.054054054054054064], [1.731753944E12, 0.08571428571428573], [1.731753942E12, 0.09375000000000003], [1.731753919E12, 0.11428571428571431], [1.731753917E12, 0.08823529411764708], [1.731753915E12, 0.10000000000000002], [1.731753958E12, 0.11428571428571431], [1.731753913E12, 0.11764705882352944], [1.731753956E12, 0.09090909090909093], [1.731753911E12, 0.05555555555555555], [1.731753954E12, 0.03333333333333333], [1.731753929E12, 0.08571428571428573], [1.731753927E12, 0.09677419354838712], [1.731753925E12, 0.11428571428571431], [1.731753923E12, 0.08571428571428573], [1.731753921E12, 0.10000000000000002], [1.731753941E12, 0.09090909090909093], [1.731753939E12, 0.03333333333333335], [1.731753937E12, 0.14285714285714288], [1.731753935E12, 0.08571428571428573], [1.731753933E12, 0.10000000000000002], [1.731753931E12, 0.11428571428571431], [1.731753951E12, 0.10000000000000002], [1.731753908E12, 0.11764705882352941], [1.731753949E12, 0.05882352941176473], [1.731753906E12, 0.09375000000000003], [1.731753947E12, 0.08571428571428573], [1.731753904E12, 0.11764705882352944], [1.731753945E12, 0.10000000000000002], [1.731753902E12, 0.08333333333333334], [1.731753943E12, 0.11428571428571431], [1.7317539E12, 2.777777777777778], [1.73175392E12, 0.05714285714285714], [1.731753918E12, 0.09677419354838712], [1.731753959E12, 0.0], [1.731753916E12, 0.11428571428571431], [1.731753957E12, 0.09375000000000003], [1.731753914E12, 0.08333333333333334], [1.731753955E12, 0.11428571428571431], [1.731753912E12, 0.09677419354838712], [1.731753953E12, 0.08571428571428573], [1.73175391E12, 0.12121212121212124], [1.73175393E12, 0.10000000000000002], [1.731753928E12, 0.11428571428571431], [1.731753926E12, 0.08823529411764708], [1.731753924E12, 0.06666666666666668], [1.731753922E12, 0.11428571428571431], [1.73175394E12, 0.1428571428571429], [1.731753938E12, 0.08571428571428573], [1.731753936E12, 0.10000000000000002], [1.731753934E12, 0.08571428571428574], [1.731753932E12, 0.08571428571428573]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731753959E12, "title": "Connect Time Over Time"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getConnectTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Average Connect Time in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendConnectTimeOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Average connect time was %y ms"
                }
            };
        },
        createGraph: function () {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesConnectTimeOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotConnectTimeOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewConnectTimeOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Connect Time Over Time
function refreshConnectTimeOverTime(fixTimestamps) {
    var infos = connectTimeOverTimeInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyConnectTimeOverTime");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotConnectTimeOverTime"))) {
        infos.createGraph();
    }else {
        var choiceContainer = $("#choicesConnectTimeOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotConnectTimeOverTime", "#overviewConnectTimeOverTime");
        $('#footerConnectTimeOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var responseTimePercentilesOverTimeInfos = {
        data: {"result": {"minY": 6.0, "minX": 1.7317539E12, "maxY": 1331.0, "series": [{"data": [[1.731753909E12, 30.0], [1.731753952E12, 33.0], [1.731753907E12, 43.0], [1.73175395E12, 27.0], [1.731753905E12, 31.0], [1.731753948E12, 26.0], [1.731753903E12, 36.0], [1.731753946E12, 43.0], [1.731753901E12, 135.0], [1.731753944E12, 34.0], [1.731753942E12, 19.0], [1.731753919E12, 28.0], [1.731753917E12, 26.0], [1.731753915E12, 28.0], [1.731753958E12, 24.0], [1.731753913E12, 31.0], [1.731753956E12, 34.0], [1.731753911E12, 38.0], [1.731753954E12, 27.0], [1.731753929E12, 36.0], [1.731753927E12, 19.0], [1.731753925E12, 34.0], [1.731753923E12, 26.0], [1.731753921E12, 21.0], [1.731753941E12, 35.0], [1.731753939E12, 26.0], [1.731753937E12, 33.0], [1.731753935E12, 26.0], [1.731753933E12, 26.0], [1.731753931E12, 45.0], [1.731753951E12, 18.0], [1.731753908E12, 29.0], [1.731753949E12, 28.0], [1.731753906E12, 22.0], [1.731753947E12, 25.0], [1.731753904E12, 32.0], [1.731753945E12, 25.0], [1.731753902E12, 34.0], [1.731753943E12, 24.0], [1.7317539E12, 1331.0], [1.73175392E12, 25.0], [1.731753918E12, 34.0], [1.731753959E12, 15.0], [1.731753916E12, 44.0], [1.731753957E12, 17.0], [1.731753914E12, 40.0], [1.731753955E12, 35.0], [1.731753912E12, 22.0], [1.731753953E12, 23.0], [1.73175391E12, 36.0], [1.73175393E12, 24.0], [1.731753928E12, 25.0], [1.731753926E12, 35.0], [1.731753924E12, 28.0], [1.731753922E12, 37.0], [1.73175394E12, 39.0], [1.731753938E12, 24.0], [1.731753936E12, 18.0], [1.731753934E12, 26.0], [1.731753932E12, 25.0]], "isOverall": false, "label": "Max", "isController": false}, {"data": [[1.731753909E12, 28.7], [1.731753952E12, 28.999999999999993], [1.731753907E12, 38.0], [1.73175395E12, 18.300000000000004], [1.731753905E12, 22.0], [1.731753948E12, 19.0], [1.731753903E12, 29.499999999999996], [1.731753946E12, 41.0], [1.731753901E12, 105.0], [1.731753944E12, 27.79999999999999], [1.731753942E12, 18.0], [1.731753919E12, 25.4], [1.731753917E12, 23.0], [1.731753915E12, 19.900000000000002], [1.731753958E12, 23.4], [1.731753913E12, 27.5], [1.731753956E12, 28.80000000000001], [1.731753911E12, 27.400000000000034], [1.731753954E12, 25.900000000000002], [1.731753929E12, 29.599999999999994], [1.731753927E12, 18.0], [1.731753925E12, 27.599999999999987], [1.731753923E12, 19.0], [1.731753921E12, 18.0], [1.731753941E12, 30.20000000000001], [1.731753939E12, 24.900000000000002], [1.731753937E12, 29.199999999999996], [1.731753935E12, 17.4], [1.731753933E12, 20.0], [1.731753931E12, 44.0], [1.731753951E12, 17.0], [1.731753908E12, 22.5], [1.731753949E12, 26.0], [1.731753906E12, 21.0], [1.731753947E12, 19.199999999999996], [1.731753904E12, 29.0], [1.731753945E12, 20.800000000000004], [1.731753902E12, 29.300000000000004], [1.731753943E12, 23.0], [1.7317539E12, 1184.3000000000002], [1.73175392E12, 19.4], [1.731753918E12, 26.400000000000006], [1.731753959E12, 15.0], [1.731753916E12, 43.0], [1.731753957E12, 17.0], [1.731753914E12, 29.400000000000034], [1.731753955E12, 27.79999999999999], [1.731753912E12, 20.8], [1.731753953E12, 18.0], [1.73175391E12, 33.20000000000001], [1.73175393E12, 19.900000000000002], [1.731753928E12, 25.0], [1.731753926E12, 29.0], [1.731753924E12, 26.0], [1.731753922E12, 28.599999999999987], [1.73175394E12, 27.19999999999999], [1.731753938E12, 18.4], [1.731753936E12, 17.0], [1.731753934E12, 25.0], [1.731753932E12, 19.4]], "isOverall": false, "label": "90th percentile", "isController": false}, {"data": [[1.731753909E12, 30.0], [1.731753952E12, 33.0], [1.731753907E12, 43.0], [1.73175395E12, 27.0], [1.731753905E12, 31.0], [1.731753948E12, 26.0], [1.731753903E12, 36.0], [1.731753946E12, 43.0], [1.731753901E12, 135.0], [1.731753944E12, 34.0], [1.731753942E12, 19.0], [1.731753919E12, 28.0], [1.731753917E12, 26.0], [1.731753915E12, 28.0], [1.731753958E12, 24.0], [1.731753913E12, 31.0], [1.731753956E12, 34.0], [1.731753911E12, 38.0], [1.731753954E12, 27.0], [1.731753929E12, 36.0], [1.731753927E12, 19.0], [1.731753925E12, 34.0], [1.731753923E12, 26.0], [1.731753921E12, 21.0], [1.731753941E12, 35.0], [1.731753939E12, 26.0], [1.731753937E12, 33.0], [1.731753935E12, 26.0], [1.731753933E12, 26.0], [1.731753931E12, 45.0], [1.731753951E12, 18.0], [1.731753908E12, 29.0], [1.731753949E12, 28.0], [1.731753906E12, 22.0], [1.731753947E12, 25.0], [1.731753904E12, 32.0], [1.731753945E12, 25.0], [1.731753902E12, 34.0], [1.731753943E12, 24.0], [1.7317539E12, 1331.0], [1.73175392E12, 25.0], [1.731753918E12, 34.0], [1.731753959E12, 15.0], [1.731753916E12, 44.0], [1.731753957E12, 17.0], [1.731753914E12, 40.0], [1.731753955E12, 35.0], [1.731753912E12, 22.0], [1.731753953E12, 23.0], [1.73175391E12, 36.0], [1.73175393E12, 24.0], [1.731753928E12, 25.0], [1.731753926E12, 35.0], [1.731753924E12, 28.0], [1.731753922E12, 37.0], [1.73175394E12, 39.0], [1.731753938E12, 24.0], [1.731753936E12, 18.0], [1.731753934E12, 26.0], [1.731753932E12, 25.0]], "isOverall": false, "label": "99th percentile", "isController": false}, {"data": [[1.731753909E12, 30.0], [1.731753952E12, 32.199999999999996], [1.731753907E12, 40.0], [1.73175395E12, 25.299999999999997], [1.731753905E12, 28.0], [1.731753948E12, 24.9], [1.731753903E12, 34.699999999999996], [1.731753946E12, 43.0], [1.731753901E12, 131.0], [1.731753944E12, 32.39999999999999], [1.731753942E12, 18.349999999999998], [1.731753919E12, 26.39999999999999], [1.731753917E12, 26.0], [1.731753915E12, 27.45], [1.731753958E12, 24.0], [1.731753913E12, 28.75], [1.731753956E12, 32.599999999999994], [1.731753911E12, 34.599999999999994], [1.731753954E12, 26.45], [1.731753929E12, 33.59999999999999], [1.731753927E12, 18.4], [1.731753925E12, 33.199999999999996], [1.731753923E12, 25.199999999999996], [1.731753921E12, 19.9], [1.731753941E12, 33.599999999999994], [1.731753939E12, 25.45], [1.731753937E12, 33.0], [1.731753935E12, 25.199999999999996], [1.731753933E12, 24.349999999999998], [1.731753931E12, 44.199999999999996], [1.731753951E12, 18.0], [1.731753908E12, 28.25], [1.731753949E12, 27.25], [1.731753906E12, 21.349999999999998], [1.731753947E12, 24.199999999999996], [1.731753904E12, 32.0], [1.731753945E12, 24.45], [1.731753902E12, 33.15], [1.731753943E12, 24.0], [1.7317539E12, 1331.0], [1.73175392E12, 25.0], [1.731753918E12, 31.599999999999994], [1.731753959E12, 15.0], [1.731753916E12, 44.0], [1.731753957E12, 17.0], [1.731753914E12, 35.74999999999999], [1.731753955E12, 34.199999999999996], [1.731753912E12, 21.4], [1.731753953E12, 18.99999999999998], [1.73175391E12, 36.0], [1.73175393E12, 24.0], [1.731753928E12, 25.0], [1.731753926E12, 34.25], [1.731753924E12, 27.45], [1.731753922E12, 35.39999999999999], [1.73175394E12, 34.99999999999998], [1.731753938E12, 24.0], [1.731753936E12, 18.0], [1.731753934E12, 26.0], [1.731753932E12, 24.199999999999996]], "isOverall": false, "label": "95th percentile", "isController": false}, {"data": [[1.731753909E12, 17.0], [1.731753952E12, 14.0], [1.731753907E12, 17.0], [1.73175395E12, 15.0], [1.731753905E12, 18.0], [1.731753948E12, 15.0], [1.731753903E12, 20.0], [1.731753946E12, 15.0], [1.731753901E12, 22.0], [1.731753944E12, 6.0], [1.731753942E12, 15.0], [1.731753919E12, 16.0], [1.731753917E12, 17.0], [1.731753915E12, 16.0], [1.731753958E12, 14.0], [1.731753913E12, 16.0], [1.731753956E12, 14.0], [1.731753911E12, 16.0], [1.731753954E12, 14.0], [1.731753929E12, 7.0], [1.731753927E12, 16.0], [1.731753925E12, 16.0], [1.731753923E12, 15.0], [1.731753921E12, 16.0], [1.731753941E12, 15.0], [1.731753939E12, 15.0], [1.731753937E12, 15.0], [1.731753935E12, 15.0], [1.731753933E12, 15.0], [1.731753931E12, 16.0], [1.731753951E12, 15.0], [1.731753908E12, 18.0], [1.731753949E12, 15.0], [1.731753906E12, 18.0], [1.731753947E12, 15.0], [1.731753904E12, 18.0], [1.731753945E12, 15.0], [1.731753902E12, 21.0], [1.731753943E12, 15.0], [1.7317539E12, 46.0], [1.73175392E12, 16.0], [1.731753918E12, 16.0], [1.731753959E12, 14.0], [1.731753916E12, 16.0], [1.731753957E12, 14.0], [1.731753914E12, 8.0], [1.731753955E12, 14.0], [1.731753912E12, 16.0], [1.731753953E12, 14.0], [1.73175391E12, 17.0], [1.73175393E12, 15.0], [1.731753928E12, 15.0], [1.731753926E12, 15.0], [1.731753924E12, 16.0], [1.731753922E12, 17.0], [1.73175394E12, 15.0], [1.731753938E12, 15.0], [1.731753936E12, 15.0], [1.731753934E12, 15.0], [1.731753932E12, 16.0]], "isOverall": false, "label": "Min", "isController": false}, {"data": [[1.731753909E12, 19.0], [1.731753952E12, 15.0], [1.731753907E12, 19.0], [1.73175395E12, 16.0], [1.731753905E12, 19.5], [1.731753948E12, 16.0], [1.731753903E12, 21.5], [1.731753946E12, 16.0], [1.731753901E12, 59.0], [1.731753944E12, 16.0], [1.731753942E12, 16.0], [1.731753919E12, 17.0], [1.731753917E12, 18.0], [1.731753915E12, 18.0], [1.731753958E12, 16.0], [1.731753913E12, 17.0], [1.731753956E12, 16.0], [1.731753911E12, 17.0], [1.731753954E12, 16.0], [1.731753929E12, 16.0], [1.731753927E12, 16.0], [1.731753925E12, 17.0], [1.731753923E12, 17.0], [1.731753921E12, 17.0], [1.731753941E12, 16.0], [1.731753939E12, 16.0], [1.731753937E12, 16.0], [1.731753935E12, 16.0], [1.731753933E12, 16.0], [1.731753931E12, 17.0], [1.731753951E12, 15.0], [1.731753908E12, 19.0], [1.731753949E12, 17.0], [1.731753906E12, 19.0], [1.731753947E12, 16.0], [1.731753904E12, 21.0], [1.731753945E12, 16.0], [1.731753902E12, 23.0], [1.731753943E12, 16.0], [1.7317539E12, 102.0], [1.73175392E12, 17.0], [1.731753918E12, 17.0], [1.731753959E12, 15.0], [1.731753916E12, 18.0], [1.731753957E12, 15.0], [1.731753914E12, 18.0], [1.731753955E12, 15.0], [1.731753912E12, 17.0], [1.731753953E12, 15.0], [1.73175391E12, 19.0], [1.73175393E12, 17.0], [1.731753928E12, 16.0], [1.731753926E12, 17.0], [1.731753924E12, 17.0], [1.731753922E12, 17.0], [1.73175394E12, 16.0], [1.731753938E12, 16.0], [1.731753936E12, 16.0], [1.731753934E12, 17.0], [1.731753932E12, 16.0]], "isOverall": false, "label": "Median", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731753959E12, "title": "Response Time Percentiles Over Time (successful requests only)"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true,
                        fill: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Response Time in ms",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: '#legendResponseTimePercentilesOverTime'
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s : at %x Response time was %y ms"
                }
            };
        },
        createGraph: function () {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesResponseTimePercentilesOverTime"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotResponseTimePercentilesOverTime"), dataset, options);
            // setup overview
            $.plot($("#overviewResponseTimePercentilesOverTime"), dataset, prepareOverviewOptions(options));
        }
};

// Response Time Percentiles Over Time
function refreshResponseTimePercentilesOverTime(fixTimestamps) {
    var infos = responseTimePercentilesOverTimeInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotResponseTimePercentilesOverTime"))) {
        infos.createGraph();
    }else {
        var choiceContainer = $("#choicesResponseTimePercentilesOverTime");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimePercentilesOverTime", "#overviewResponseTimePercentilesOverTime");
        $('#footerResponseTimePercentilesOverTime .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};


var responseTimeVsRequestInfos = {
    data: {"result": {"minY": 15.0, "minX": 5.0, "maxY": 102.0, "series": [{"data": [[32.0, 19.0], [33.0, 17.0], [34.0, 19.0], [35.0, 16.0], [18.0, 102.0], [74.0, 59.0], [36.0, 18.0], [5.0, 15.0], [30.0, 16.0], [31.0, 17.0]], "isOverall": false, "label": "Successes", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 74.0, "title": "Response Time Vs Request"}},
    getOptions: function() {
        return {
            series: {
                lines: {
                    show: false
                },
                points: {
                    show: true
                }
            },
            xaxis: {
                axisLabel: "Global number of requests per second",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            yaxis: {
                axisLabel: "Median Response Time in ms",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            legend: {
                noColumns: 2,
                show: true,
                container: '#legendResponseTimeVsRequest'
            },
            selection: {
                mode: 'xy'
            },
            grid: {
                hoverable: true // IMPORTANT! this is needed for tooltip to work
            },
            tooltip: true,
            tooltipOpts: {
                content: "%s : Median response time at %x req/s was %y ms"
            },
            colors: ["#9ACD32", "#FF6347"]
        };
    },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesResponseTimeVsRequest"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotResponseTimeVsRequest"), dataset, options);
        // setup overview
        $.plot($("#overviewResponseTimeVsRequest"), dataset, prepareOverviewOptions(options));

    }
};

// Response Time vs Request
function refreshResponseTimeVsRequest() {
    var infos = responseTimeVsRequestInfos;
    prepareSeries(infos.data);
    if (isGraph($("#flotResponseTimeVsRequest"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesResponseTimeVsRequest");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotResponseTimeVsRequest", "#overviewResponseTimeVsRequest");
        $('#footerResponseRimeVsRequest .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};


var latenciesVsRequestInfos = {
    data: {"result": {"minY": 15.0, "minX": 5.0, "maxY": 102.0, "series": [{"data": [[32.0, 19.0], [33.0, 17.0], [34.0, 18.5], [35.0, 16.0], [18.0, 102.0], [74.0, 58.5], [36.0, 18.0], [5.0, 15.0], [30.0, 16.0], [31.0, 17.0]], "isOverall": false, "label": "Successes", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 74.0, "title": "Latencies Vs Request"}},
    getOptions: function() {
        return{
            series: {
                lines: {
                    show: false
                },
                points: {
                    show: true
                }
            },
            xaxis: {
                axisLabel: "Global number of requests per second",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            yaxis: {
                axisLabel: "Median Latency in ms",
                axisLabelUseCanvas: true,
                axisLabelFontSizePixels: 12,
                axisLabelFontFamily: 'Verdana, Arial',
                axisLabelPadding: 20,
            },
            legend: { noColumns: 2,show: true, container: '#legendLatencyVsRequest' },
            selection: {
                mode: 'xy'
            },
            grid: {
                hoverable: true // IMPORTANT! this is needed for tooltip to work
            },
            tooltip: true,
            tooltipOpts: {
                content: "%s : Median Latency time at %x req/s was %y ms"
            },
            colors: ["#9ACD32", "#FF6347"]
        };
    },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesLatencyVsRequest"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotLatenciesVsRequest"), dataset, options);
        // setup overview
        $.plot($("#overviewLatenciesVsRequest"), dataset, prepareOverviewOptions(options));
    }
};

// Latencies vs Request
function refreshLatenciesVsRequest() {
        var infos = latenciesVsRequestInfos;
        prepareSeries(infos.data);
        if(isGraph($("#flotLatenciesVsRequest"))){
            infos.createGraph();
        }else{
            var choiceContainer = $("#choicesLatencyVsRequest");
            createLegend(choiceContainer, infos);
            infos.createGraph();
            setGraphZoomable("#flotLatenciesVsRequest", "#overviewLatenciesVsRequest");
            $('#footerLatenciesVsRequest .legendColorBox > div').each(function(i){
                $(this).clone().prependTo(choiceContainer.find("li").eq(i));
            });
        }
};

var hitsPerSecondInfos = {
        data: {"result": {"minY": 3.0, "minX": 1.731753899E12, "maxY": 69.0, "series": [{"data": [[1.731753909E12, 31.0], [1.731753952E12, 36.0], [1.731753907E12, 35.0], [1.73175395E12, 35.0], [1.731753905E12, 34.0], [1.731753948E12, 30.0], [1.731753903E12, 31.0], [1.731753946E12, 36.0], [1.731753901E12, 69.0], [1.731753944E12, 34.0], [1.731753899E12, 3.0], [1.731753942E12, 31.0], [1.731753919E12, 36.0], [1.731753917E12, 34.0], [1.731753915E12, 30.0], [1.731753958E12, 36.0], [1.731753913E12, 35.0], [1.731753956E12, 33.0], [1.731753911E12, 36.0], [1.731753954E12, 30.0], [1.731753929E12, 34.0], [1.731753927E12, 30.0], [1.731753925E12, 36.0], [1.731753923E12, 34.0], [1.731753921E12, 30.0], [1.731753941E12, 33.0], [1.731753939E12, 30.0], [1.731753937E12, 36.0], [1.731753935E12, 34.0], [1.731753933E12, 30.0], [1.731753931E12, 36.0], [1.731753951E12, 30.0], [1.731753908E12, 34.0], [1.731753949E12, 35.0], [1.731753906E12, 31.0], [1.731753947E12, 34.0], [1.731753904E12, 35.0], [1.731753945E12, 30.0], [1.731753902E12, 36.0], [1.731753943E12, 36.0], [1.7317539E12, 21.0], [1.73175392E12, 34.0], [1.731753918E12, 30.0], [1.731753959E12, 4.0], [1.731753916E12, 36.0], [1.731753957E12, 31.0], [1.731753914E12, 35.0], [1.731753955E12, 36.0], [1.731753912E12, 30.0], [1.731753953E12, 34.0], [1.73175391E12, 34.0], [1.73175393E12, 30.0], [1.731753928E12, 36.0], [1.731753926E12, 34.0], [1.731753924E12, 30.0], [1.731753922E12, 36.0], [1.73175394E12, 36.0], [1.731753938E12, 34.0], [1.731753936E12, 30.0], [1.731753934E12, 36.0], [1.731753932E12, 34.0]], "isOverall": false, "label": "hitsPerSecond", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731753959E12, "title": "Hits Per Second"}},
        getOptions: function() {
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of hits / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendHitsPerSecond"
                },
                selection: {
                    mode : 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y.2 hits/sec"
                }
            };
        },
        createGraph: function createGraph() {
            var data = this.data;
            var dataset = prepareData(data.result.series, $("#choicesHitsPerSecond"));
            var options = this.getOptions();
            prepareOptions(options, data);
            $.plot($("#flotHitsPerSecond"), dataset, options);
            // setup overview
            $.plot($("#overviewHitsPerSecond"), dataset, prepareOverviewOptions(options));
        }
};

// Hits per second
function refreshHitsPerSecond(fixTimestamps) {
    var infos = hitsPerSecondInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if (isGraph($("#flotHitsPerSecond"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesHitsPerSecond");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotHitsPerSecond", "#overviewHitsPerSecond");
        $('#footerHitsPerSecond .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
}

var codesPerSecondInfos = {
        data: {"result": {"minY": 5.0, "minX": 1.7317539E12, "maxY": 74.0, "series": [{"data": [[1.731753909E12, 32.0], [1.731753952E12, 35.0], [1.731753907E12, 34.0], [1.73175395E12, 36.0], [1.731753905E12, 34.0], [1.731753948E12, 30.0], [1.731753903E12, 32.0], [1.731753946E12, 35.0], [1.731753901E12, 74.0], [1.731753944E12, 35.0], [1.731753942E12, 32.0], [1.731753919E12, 35.0], [1.731753917E12, 34.0], [1.731753915E12, 30.0], [1.731753958E12, 35.0], [1.731753913E12, 34.0], [1.731753956E12, 33.0], [1.731753911E12, 36.0], [1.731753954E12, 30.0], [1.731753929E12, 35.0], [1.731753927E12, 31.0], [1.731753925E12, 35.0], [1.731753923E12, 35.0], [1.731753921E12, 30.0], [1.731753941E12, 33.0], [1.731753939E12, 30.0], [1.731753937E12, 35.0], [1.731753935E12, 35.0], [1.731753933E12, 30.0], [1.731753931E12, 35.0], [1.731753951E12, 30.0], [1.731753908E12, 34.0], [1.731753949E12, 34.0], [1.731753906E12, 32.0], [1.731753947E12, 35.0], [1.731753904E12, 34.0], [1.731753945E12, 30.0], [1.731753902E12, 36.0], [1.731753943E12, 35.0], [1.7317539E12, 18.0], [1.73175392E12, 35.0], [1.731753918E12, 31.0], [1.731753959E12, 5.0], [1.731753916E12, 35.0], [1.731753957E12, 32.0], [1.731753914E12, 36.0], [1.731753955E12, 35.0], [1.731753912E12, 31.0], [1.731753953E12, 35.0], [1.73175391E12, 33.0], [1.73175393E12, 30.0], [1.731753928E12, 35.0], [1.731753926E12, 34.0], [1.731753924E12, 30.0], [1.731753922E12, 35.0], [1.73175394E12, 35.0], [1.731753938E12, 35.0], [1.731753936E12, 30.0], [1.731753934E12, 35.0], [1.731753932E12, 35.0]], "isOverall": false, "label": "200", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731753959E12, "title": "Codes Per Second"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of responses / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendCodesPerSecond"
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "Number of Response Codes %s at %x was %y.2 responses / sec"
                }
            };
        },
    createGraph: function() {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesCodesPerSecond"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotCodesPerSecond"), dataset, options);
        // setup overview
        $.plot($("#overviewCodesPerSecond"), dataset, prepareOverviewOptions(options));
    }
};

// Codes per second
function refreshCodesPerSecond(fixTimestamps) {
    var infos = codesPerSecondInfos;
    prepareSeries(infos.data);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotCodesPerSecond"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesCodesPerSecond");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotCodesPerSecond", "#overviewCodesPerSecond");
        $('#footerCodesPerSecond .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var transactionsPerSecondInfos = {
        data: {"result": {"minY": 5.0, "minX": 1.7317539E12, "maxY": 74.0, "series": [{"data": [[1.731753909E12, 32.0], [1.731753952E12, 35.0], [1.731753907E12, 34.0], [1.73175395E12, 36.0], [1.731753905E12, 34.0], [1.731753948E12, 30.0], [1.731753903E12, 32.0], [1.731753946E12, 35.0], [1.731753901E12, 74.0], [1.731753944E12, 35.0], [1.731753942E12, 32.0], [1.731753919E12, 35.0], [1.731753917E12, 34.0], [1.731753915E12, 30.0], [1.731753958E12, 35.0], [1.731753913E12, 34.0], [1.731753956E12, 33.0], [1.731753911E12, 36.0], [1.731753954E12, 30.0], [1.731753929E12, 35.0], [1.731753927E12, 31.0], [1.731753925E12, 35.0], [1.731753923E12, 35.0], [1.731753921E12, 30.0], [1.731753941E12, 33.0], [1.731753939E12, 30.0], [1.731753937E12, 35.0], [1.731753935E12, 35.0], [1.731753933E12, 30.0], [1.731753931E12, 35.0], [1.731753951E12, 30.0], [1.731753908E12, 34.0], [1.731753949E12, 34.0], [1.731753906E12, 32.0], [1.731753947E12, 35.0], [1.731753904E12, 34.0], [1.731753945E12, 30.0], [1.731753902E12, 36.0], [1.731753943E12, 35.0], [1.7317539E12, 18.0], [1.73175392E12, 35.0], [1.731753918E12, 31.0], [1.731753959E12, 5.0], [1.731753916E12, 35.0], [1.731753957E12, 32.0], [1.731753914E12, 36.0], [1.731753955E12, 35.0], [1.731753912E12, 31.0], [1.731753953E12, 35.0], [1.73175391E12, 33.0], [1.73175393E12, 30.0], [1.731753928E12, 35.0], [1.731753926E12, 34.0], [1.731753924E12, 30.0], [1.731753922E12, 35.0], [1.73175394E12, 35.0], [1.731753938E12, 35.0], [1.731753936E12, 30.0], [1.731753934E12, 35.0], [1.731753932E12, 35.0]], "isOverall": false, "label": "Products-success", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731753959E12, "title": "Transactions Per Second"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of transactions / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendTransactionsPerSecond"
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y transactions / sec"
                }
            };
        },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesTransactionsPerSecond"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotTransactionsPerSecond"), dataset, options);
        // setup overview
        $.plot($("#overviewTransactionsPerSecond"), dataset, prepareOverviewOptions(options));
    }
};

// Transactions per second
function refreshTransactionsPerSecond(fixTimestamps) {
    var infos = transactionsPerSecondInfos;
    prepareSeries(infos.data);
    if(infos.data.result.series.length == 0) {
        setEmptyGraph("#bodyTransactionsPerSecond");
        return;
    }
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotTransactionsPerSecond"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesTransactionsPerSecond");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotTransactionsPerSecond", "#overviewTransactionsPerSecond");
        $('#footerTransactionsPerSecond .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

var totalTPSInfos = {
        data: {"result": {"minY": 5.0, "minX": 1.7317539E12, "maxY": 74.0, "series": [{"data": [[1.731753909E12, 32.0], [1.731753952E12, 35.0], [1.731753907E12, 34.0], [1.73175395E12, 36.0], [1.731753905E12, 34.0], [1.731753948E12, 30.0], [1.731753903E12, 32.0], [1.731753946E12, 35.0], [1.731753901E12, 74.0], [1.731753944E12, 35.0], [1.731753942E12, 32.0], [1.731753919E12, 35.0], [1.731753917E12, 34.0], [1.731753915E12, 30.0], [1.731753958E12, 35.0], [1.731753913E12, 34.0], [1.731753956E12, 33.0], [1.731753911E12, 36.0], [1.731753954E12, 30.0], [1.731753929E12, 35.0], [1.731753927E12, 31.0], [1.731753925E12, 35.0], [1.731753923E12, 35.0], [1.731753921E12, 30.0], [1.731753941E12, 33.0], [1.731753939E12, 30.0], [1.731753937E12, 35.0], [1.731753935E12, 35.0], [1.731753933E12, 30.0], [1.731753931E12, 35.0], [1.731753951E12, 30.0], [1.731753908E12, 34.0], [1.731753949E12, 34.0], [1.731753906E12, 32.0], [1.731753947E12, 35.0], [1.731753904E12, 34.0], [1.731753945E12, 30.0], [1.731753902E12, 36.0], [1.731753943E12, 35.0], [1.7317539E12, 18.0], [1.73175392E12, 35.0], [1.731753918E12, 31.0], [1.731753959E12, 5.0], [1.731753916E12, 35.0], [1.731753957E12, 32.0], [1.731753914E12, 36.0], [1.731753955E12, 35.0], [1.731753912E12, 31.0], [1.731753953E12, 35.0], [1.73175391E12, 33.0], [1.73175393E12, 30.0], [1.731753928E12, 35.0], [1.731753926E12, 34.0], [1.731753924E12, 30.0], [1.731753922E12, 35.0], [1.73175394E12, 35.0], [1.731753938E12, 35.0], [1.731753936E12, 30.0], [1.731753934E12, 35.0], [1.731753932E12, 35.0]], "isOverall": false, "label": "Transaction-success", "isController": false}, {"data": [], "isOverall": false, "label": "Transaction-failure", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731753959E12, "title": "Total Transactions Per Second"}},
        getOptions: function(){
            return {
                series: {
                    lines: {
                        show: true
                    },
                    points: {
                        show: true
                    }
                },
                xaxis: {
                    mode: "time",
                    timeformat: getTimeFormat(this.data.result.granularity),
                    axisLabel: getElapsedTimeLabel(this.data.result.granularity),
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20,
                },
                yaxis: {
                    axisLabel: "Number of transactions / sec",
                    axisLabelUseCanvas: true,
                    axisLabelFontSizePixels: 12,
                    axisLabelFontFamily: 'Verdana, Arial',
                    axisLabelPadding: 20
                },
                legend: {
                    noColumns: 2,
                    show: true,
                    container: "#legendTotalTPS"
                },
                selection: {
                    mode: 'xy'
                },
                grid: {
                    hoverable: true // IMPORTANT! this is needed for tooltip to
                                    // work
                },
                tooltip: true,
                tooltipOpts: {
                    content: "%s at %x was %y transactions / sec"
                },
                colors: ["#9ACD32", "#FF6347"]
            };
        },
    createGraph: function () {
        var data = this.data;
        var dataset = prepareData(data.result.series, $("#choicesTotalTPS"));
        var options = this.getOptions();
        prepareOptions(options, data);
        $.plot($("#flotTotalTPS"), dataset, options);
        // setup overview
        $.plot($("#overviewTotalTPS"), dataset, prepareOverviewOptions(options));
    }
};

// Total Transactions per second
function refreshTotalTPS(fixTimestamps) {
    var infos = totalTPSInfos;
    // We want to ignore seriesFilter
    prepareSeries(infos.data, false, true);
    if(fixTimestamps) {
        fixTimeStamps(infos.data.result.series, 28800000);
    }
    if(isGraph($("#flotTotalTPS"))){
        infos.createGraph();
    }else{
        var choiceContainer = $("#choicesTotalTPS");
        createLegend(choiceContainer, infos);
        infos.createGraph();
        setGraphZoomable("#flotTotalTPS", "#overviewTotalTPS");
        $('#footerTotalTPS .legendColorBox > div').each(function(i){
            $(this).clone().prependTo(choiceContainer.find("li").eq(i));
        });
    }
};

// Collapse the graph matching the specified DOM element depending the collapsed
// status
function collapse(elem, collapsed){
    if(collapsed){
        $(elem).parent().find(".fa-chevron-up").removeClass("fa-chevron-up").addClass("fa-chevron-down");
    } else {
        $(elem).parent().find(".fa-chevron-down").removeClass("fa-chevron-down").addClass("fa-chevron-up");
        if (elem.id == "bodyBytesThroughputOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshBytesThroughputOverTime(true);
            }
            document.location.href="#bytesThroughputOverTime";
        } else if (elem.id == "bodyLatenciesOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshLatenciesOverTime(true);
            }
            document.location.href="#latenciesOverTime";
        } else if (elem.id == "bodyCustomGraph") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshCustomGraph(true);
            }
            document.location.href="#responseCustomGraph";
        } else if (elem.id == "bodyConnectTimeOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshConnectTimeOverTime(true);
            }
            document.location.href="#connectTimeOverTime";
        } else if (elem.id == "bodyResponseTimePercentilesOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshResponseTimePercentilesOverTime(true);
            }
            document.location.href="#responseTimePercentilesOverTime";
        } else if (elem.id == "bodyResponseTimeDistribution") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshResponseTimeDistribution();
            }
            document.location.href="#responseTimeDistribution" ;
        } else if (elem.id == "bodySyntheticResponseTimeDistribution") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshSyntheticResponseTimeDistribution();
            }
            document.location.href="#syntheticResponseTimeDistribution" ;
        } else if (elem.id == "bodyActiveThreadsOverTime") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshActiveThreadsOverTime(true);
            }
            document.location.href="#activeThreadsOverTime";
        } else if (elem.id == "bodyTimeVsThreads") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshTimeVsThreads();
            }
            document.location.href="#timeVsThreads" ;
        } else if (elem.id == "bodyCodesPerSecond") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshCodesPerSecond(true);
            }
            document.location.href="#codesPerSecond";
        } else if (elem.id == "bodyTransactionsPerSecond") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshTransactionsPerSecond(true);
            }
            document.location.href="#transactionsPerSecond";
        } else if (elem.id == "bodyTotalTPS") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshTotalTPS(true);
            }
            document.location.href="#totalTPS";
        } else if (elem.id == "bodyResponseTimeVsRequest") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshResponseTimeVsRequest();
            }
            document.location.href="#responseTimeVsRequest";
        } else if (elem.id == "bodyLatenciesVsRequest") {
            if (isGraph($(elem).find('.flot-chart-content')) == false) {
                refreshLatenciesVsRequest();
            }
            document.location.href="#latencyVsRequest";
        }
    }
}

/*
 * Activates or deactivates all series of the specified graph (represented by id parameter)
 * depending on checked argument.
 */
function toggleAll(id, checked){
    var placeholder = document.getElementById(id);

    var cases = $(placeholder).find(':checkbox');
    cases.prop('checked', checked);
    $(cases).parent().children().children().toggleClass("legend-disabled", !checked);

    var choiceContainer;
    if ( id == "choicesBytesThroughputOverTime"){
        choiceContainer = $("#choicesBytesThroughputOverTime");
        refreshBytesThroughputOverTime(false);
    } else if(id == "choicesResponseTimesOverTime"){
        choiceContainer = $("#choicesResponseTimesOverTime");
        refreshResponseTimeOverTime(false);
    }else if(id == "choicesResponseCustomGraph"){
        choiceContainer = $("#choicesResponseCustomGraph");
        refreshCustomGraph(false);
    } else if ( id == "choicesLatenciesOverTime"){
        choiceContainer = $("#choicesLatenciesOverTime");
        refreshLatenciesOverTime(false);
    } else if ( id == "choicesConnectTimeOverTime"){
        choiceContainer = $("#choicesConnectTimeOverTime");
        refreshConnectTimeOverTime(false);
    } else if ( id == "choicesResponseTimePercentilesOverTime"){
        choiceContainer = $("#choicesResponseTimePercentilesOverTime");
        refreshResponseTimePercentilesOverTime(false);
    } else if ( id == "choicesResponseTimePercentiles"){
        choiceContainer = $("#choicesResponseTimePercentiles");
        refreshResponseTimePercentiles();
    } else if(id == "choicesActiveThreadsOverTime"){
        choiceContainer = $("#choicesActiveThreadsOverTime");
        refreshActiveThreadsOverTime(false);
    } else if ( id == "choicesTimeVsThreads"){
        choiceContainer = $("#choicesTimeVsThreads");
        refreshTimeVsThreads();
    } else if ( id == "choicesSyntheticResponseTimeDistribution"){
        choiceContainer = $("#choicesSyntheticResponseTimeDistribution");
        refreshSyntheticResponseTimeDistribution();
    } else if ( id == "choicesResponseTimeDistribution"){
        choiceContainer = $("#choicesResponseTimeDistribution");
        refreshResponseTimeDistribution();
    } else if ( id == "choicesHitsPerSecond"){
        choiceContainer = $("#choicesHitsPerSecond");
        refreshHitsPerSecond(false);
    } else if(id == "choicesCodesPerSecond"){
        choiceContainer = $("#choicesCodesPerSecond");
        refreshCodesPerSecond(false);
    } else if ( id == "choicesTransactionsPerSecond"){
        choiceContainer = $("#choicesTransactionsPerSecond");
        refreshTransactionsPerSecond(false);
    } else if ( id == "choicesTotalTPS"){
        choiceContainer = $("#choicesTotalTPS");
        refreshTotalTPS(false);
    } else if ( id == "choicesResponseTimeVsRequest"){
        choiceContainer = $("#choicesResponseTimeVsRequest");
        refreshResponseTimeVsRequest();
    } else if ( id == "choicesLatencyVsRequest"){
        choiceContainer = $("#choicesLatencyVsRequest");
        refreshLatenciesVsRequest();
    }
    var color = checked ? "black" : "#818181";
    if(choiceContainer != null) {
        choiceContainer.find("label").each(function(){
            this.style.color = color;
        });
    }
}

