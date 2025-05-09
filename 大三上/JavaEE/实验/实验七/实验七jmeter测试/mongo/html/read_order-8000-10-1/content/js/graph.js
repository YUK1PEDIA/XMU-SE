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
        data: {"result": {"minY": 1.0, "minX": 0.0, "maxY": 131.0, "series": [{"data": [[0.0, 1.0], [0.1, 1.0], [0.2, 1.0], [0.3, 1.0], [0.4, 1.0], [0.5, 1.0], [0.6, 1.0], [0.7, 1.0], [0.8, 1.0], [0.9, 1.0], [1.0, 1.0], [1.1, 1.0], [1.2, 1.0], [1.3, 1.0], [1.4, 1.0], [1.5, 1.0], [1.6, 1.0], [1.7, 1.0], [1.8, 1.0], [1.9, 1.0], [2.0, 1.0], [2.1, 1.0], [2.2, 1.0], [2.3, 1.0], [2.4, 1.0], [2.5, 1.0], [2.6, 1.0], [2.7, 1.0], [2.8, 1.0], [2.9, 1.0], [3.0, 1.0], [3.1, 1.0], [3.2, 1.0], [3.3, 1.0], [3.4, 1.0], [3.5, 1.0], [3.6, 1.0], [3.7, 1.0], [3.8, 1.0], [3.9, 1.0], [4.0, 1.0], [4.1, 1.0], [4.2, 1.0], [4.3, 1.0], [4.4, 1.0], [4.5, 1.0], [4.6, 1.0], [4.7, 1.0], [4.8, 1.0], [4.9, 1.0], [5.0, 1.0], [5.1, 1.0], [5.2, 1.0], [5.3, 2.0], [5.4, 2.0], [5.5, 2.0], [5.6, 2.0], [5.7, 2.0], [5.8, 2.0], [5.9, 2.0], [6.0, 2.0], [6.1, 2.0], [6.2, 2.0], [6.3, 2.0], [6.4, 2.0], [6.5, 2.0], [6.6, 2.0], [6.7, 2.0], [6.8, 2.0], [6.9, 2.0], [7.0, 2.0], [7.1, 2.0], [7.2, 2.0], [7.3, 2.0], [7.4, 2.0], [7.5, 2.0], [7.6, 2.0], [7.7, 2.0], [7.8, 2.0], [7.9, 2.0], [8.0, 2.0], [8.1, 2.0], [8.2, 2.0], [8.3, 2.0], [8.4, 2.0], [8.5, 2.0], [8.6, 2.0], [8.7, 2.0], [8.8, 2.0], [8.9, 2.0], [9.0, 2.0], [9.1, 2.0], [9.2, 2.0], [9.3, 2.0], [9.4, 2.0], [9.5, 2.0], [9.6, 2.0], [9.7, 2.0], [9.8, 2.0], [9.9, 2.0], [10.0, 2.0], [10.1, 2.0], [10.2, 2.0], [10.3, 2.0], [10.4, 2.0], [10.5, 2.0], [10.6, 2.0], [10.7, 2.0], [10.8, 2.0], [10.9, 2.0], [11.0, 2.0], [11.1, 2.0], [11.2, 2.0], [11.3, 2.0], [11.4, 2.0], [11.5, 2.0], [11.6, 2.0], [11.7, 2.0], [11.8, 2.0], [11.9, 2.0], [12.0, 2.0], [12.1, 2.0], [12.2, 2.0], [12.3, 2.0], [12.4, 2.0], [12.5, 2.0], [12.6, 2.0], [12.7, 2.0], [12.8, 2.0], [12.9, 2.0], [13.0, 2.0], [13.1, 2.0], [13.2, 2.0], [13.3, 2.0], [13.4, 2.0], [13.5, 2.0], [13.6, 2.0], [13.7, 2.0], [13.8, 2.0], [13.9, 2.0], [14.0, 2.0], [14.1, 2.0], [14.2, 2.0], [14.3, 2.0], [14.4, 2.0], [14.5, 2.0], [14.6, 2.0], [14.7, 2.0], [14.8, 2.0], [14.9, 2.0], [15.0, 2.0], [15.1, 2.0], [15.2, 2.0], [15.3, 2.0], [15.4, 2.0], [15.5, 2.0], [15.6, 2.0], [15.7, 2.0], [15.8, 2.0], [15.9, 2.0], [16.0, 2.0], [16.1, 2.0], [16.2, 2.0], [16.3, 2.0], [16.4, 2.0], [16.5, 2.0], [16.6, 2.0], [16.7, 2.0], [16.8, 2.0], [16.9, 2.0], [17.0, 2.0], [17.1, 2.0], [17.2, 2.0], [17.3, 2.0], [17.4, 2.0], [17.5, 2.0], [17.6, 2.0], [17.7, 2.0], [17.8, 2.0], [17.9, 2.0], [18.0, 2.0], [18.1, 2.0], [18.2, 2.0], [18.3, 2.0], [18.4, 2.0], [18.5, 2.0], [18.6, 2.0], [18.7, 2.0], [18.8, 2.0], [18.9, 2.0], [19.0, 2.0], [19.1, 2.0], [19.2, 2.0], [19.3, 2.0], [19.4, 2.0], [19.5, 2.0], [19.6, 2.0], [19.7, 2.0], [19.8, 2.0], [19.9, 2.0], [20.0, 2.0], [20.1, 2.0], [20.2, 2.0], [20.3, 2.0], [20.4, 2.0], [20.5, 2.0], [20.6, 2.0], [20.7, 2.0], [20.8, 2.0], [20.9, 2.0], [21.0, 2.0], [21.1, 2.0], [21.2, 2.0], [21.3, 2.0], [21.4, 2.0], [21.5, 2.0], [21.6, 2.0], [21.7, 2.0], [21.8, 2.0], [21.9, 2.0], [22.0, 2.0], [22.1, 2.0], [22.2, 2.0], [22.3, 2.0], [22.4, 2.0], [22.5, 2.0], [22.6, 2.0], [22.7, 2.0], [22.8, 2.0], [22.9, 2.0], [23.0, 2.0], [23.1, 2.0], [23.2, 2.0], [23.3, 2.0], [23.4, 2.0], [23.5, 2.0], [23.6, 2.0], [23.7, 2.0], [23.8, 2.0], [23.9, 2.0], [24.0, 2.0], [24.1, 2.0], [24.2, 2.0], [24.3, 2.0], [24.4, 2.0], [24.5, 2.0], [24.6, 2.0], [24.7, 2.0], [24.8, 2.0], [24.9, 2.0], [25.0, 2.0], [25.1, 2.0], [25.2, 2.0], [25.3, 2.0], [25.4, 2.0], [25.5, 2.0], [25.6, 2.0], [25.7, 2.0], [25.8, 2.0], [25.9, 2.0], [26.0, 2.0], [26.1, 2.0], [26.2, 2.0], [26.3, 2.0], [26.4, 2.0], [26.5, 2.0], [26.6, 2.0], [26.7, 2.0], [26.8, 2.0], [26.9, 2.0], [27.0, 2.0], [27.1, 2.0], [27.2, 2.0], [27.3, 2.0], [27.4, 2.0], [27.5, 2.0], [27.6, 2.0], [27.7, 2.0], [27.8, 2.0], [27.9, 2.0], [28.0, 2.0], [28.1, 2.0], [28.2, 2.0], [28.3, 2.0], [28.4, 2.0], [28.5, 2.0], [28.6, 2.0], [28.7, 2.0], [28.8, 2.0], [28.9, 2.0], [29.0, 2.0], [29.1, 2.0], [29.2, 2.0], [29.3, 2.0], [29.4, 2.0], [29.5, 2.0], [29.6, 2.0], [29.7, 2.0], [29.8, 2.0], [29.9, 2.0], [30.0, 2.0], [30.1, 2.0], [30.2, 2.0], [30.3, 2.0], [30.4, 2.0], [30.5, 2.0], [30.6, 2.0], [30.7, 2.0], [30.8, 2.0], [30.9, 2.0], [31.0, 2.0], [31.1, 2.0], [31.2, 2.0], [31.3, 2.0], [31.4, 2.0], [31.5, 2.0], [31.6, 2.0], [31.7, 2.0], [31.8, 2.0], [31.9, 2.0], [32.0, 2.0], [32.1, 2.0], [32.2, 2.0], [32.3, 2.0], [32.4, 2.0], [32.5, 2.0], [32.6, 2.0], [32.7, 2.0], [32.8, 2.0], [32.9, 2.0], [33.0, 2.0], [33.1, 2.0], [33.2, 2.0], [33.3, 2.0], [33.4, 2.0], [33.5, 2.0], [33.6, 2.0], [33.7, 2.0], [33.8, 2.0], [33.9, 2.0], [34.0, 2.0], [34.1, 2.0], [34.2, 2.0], [34.3, 2.0], [34.4, 2.0], [34.5, 2.0], [34.6, 2.0], [34.7, 2.0], [34.8, 2.0], [34.9, 2.0], [35.0, 2.0], [35.1, 2.0], [35.2, 2.0], [35.3, 2.0], [35.4, 2.0], [35.5, 2.0], [35.6, 2.0], [35.7, 2.0], [35.8, 2.0], [35.9, 2.0], [36.0, 2.0], [36.1, 2.0], [36.2, 2.0], [36.3, 2.0], [36.4, 2.0], [36.5, 2.0], [36.6, 2.0], [36.7, 2.0], [36.8, 2.0], [36.9, 2.0], [37.0, 2.0], [37.1, 2.0], [37.2, 2.0], [37.3, 2.0], [37.4, 2.0], [37.5, 2.0], [37.6, 2.0], [37.7, 2.0], [37.8, 2.0], [37.9, 2.0], [38.0, 2.0], [38.1, 2.0], [38.2, 2.0], [38.3, 2.0], [38.4, 2.0], [38.5, 2.0], [38.6, 2.0], [38.7, 2.0], [38.8, 2.0], [38.9, 2.0], [39.0, 3.0], [39.1, 3.0], [39.2, 3.0], [39.3, 3.0], [39.4, 3.0], [39.5, 3.0], [39.6, 3.0], [39.7, 3.0], [39.8, 3.0], [39.9, 3.0], [40.0, 3.0], [40.1, 3.0], [40.2, 3.0], [40.3, 3.0], [40.4, 3.0], [40.5, 3.0], [40.6, 3.0], [40.7, 3.0], [40.8, 3.0], [40.9, 3.0], [41.0, 3.0], [41.1, 3.0], [41.2, 3.0], [41.3, 3.0], [41.4, 3.0], [41.5, 3.0], [41.6, 3.0], [41.7, 3.0], [41.8, 3.0], [41.9, 3.0], [42.0, 3.0], [42.1, 3.0], [42.2, 3.0], [42.3, 3.0], [42.4, 3.0], [42.5, 3.0], [42.6, 3.0], [42.7, 3.0], [42.8, 3.0], [42.9, 3.0], [43.0, 3.0], [43.1, 3.0], [43.2, 3.0], [43.3, 3.0], [43.4, 3.0], [43.5, 3.0], [43.6, 3.0], [43.7, 3.0], [43.8, 3.0], [43.9, 3.0], [44.0, 3.0], [44.1, 3.0], [44.2, 3.0], [44.3, 3.0], [44.4, 3.0], [44.5, 3.0], [44.6, 3.0], [44.7, 3.0], [44.8, 3.0], [44.9, 3.0], [45.0, 3.0], [45.1, 3.0], [45.2, 3.0], [45.3, 3.0], [45.4, 3.0], [45.5, 3.0], [45.6, 3.0], [45.7, 3.0], [45.8, 3.0], [45.9, 3.0], [46.0, 3.0], [46.1, 3.0], [46.2, 3.0], [46.3, 3.0], [46.4, 3.0], [46.5, 3.0], [46.6, 3.0], [46.7, 3.0], [46.8, 3.0], [46.9, 3.0], [47.0, 3.0], [47.1, 3.0], [47.2, 3.0], [47.3, 3.0], [47.4, 3.0], [47.5, 3.0], [47.6, 3.0], [47.7, 3.0], [47.8, 3.0], [47.9, 3.0], [48.0, 3.0], [48.1, 3.0], [48.2, 3.0], [48.3, 3.0], [48.4, 3.0], [48.5, 3.0], [48.6, 3.0], [48.7, 3.0], [48.8, 3.0], [48.9, 3.0], [49.0, 3.0], [49.1, 3.0], [49.2, 3.0], [49.3, 3.0], [49.4, 3.0], [49.5, 3.0], [49.6, 3.0], [49.7, 3.0], [49.8, 3.0], [49.9, 3.0], [50.0, 3.0], [50.1, 3.0], [50.2, 3.0], [50.3, 3.0], [50.4, 3.0], [50.5, 3.0], [50.6, 3.0], [50.7, 3.0], [50.8, 3.0], [50.9, 3.0], [51.0, 3.0], [51.1, 3.0], [51.2, 3.0], [51.3, 3.0], [51.4, 3.0], [51.5, 3.0], [51.6, 3.0], [51.7, 3.0], [51.8, 3.0], [51.9, 3.0], [52.0, 3.0], [52.1, 3.0], [52.2, 3.0], [52.3, 3.0], [52.4, 3.0], [52.5, 3.0], [52.6, 3.0], [52.7, 3.0], [52.8, 3.0], [52.9, 3.0], [53.0, 3.0], [53.1, 3.0], [53.2, 3.0], [53.3, 3.0], [53.4, 3.0], [53.5, 3.0], [53.6, 3.0], [53.7, 3.0], [53.8, 3.0], [53.9, 3.0], [54.0, 3.0], [54.1, 3.0], [54.2, 3.0], [54.3, 3.0], [54.4, 3.0], [54.5, 3.0], [54.6, 3.0], [54.7, 3.0], [54.8, 3.0], [54.9, 3.0], [55.0, 3.0], [55.1, 3.0], [55.2, 3.0], [55.3, 3.0], [55.4, 3.0], [55.5, 3.0], [55.6, 3.0], [55.7, 3.0], [55.8, 3.0], [55.9, 3.0], [56.0, 3.0], [56.1, 3.0], [56.2, 3.0], [56.3, 3.0], [56.4, 3.0], [56.5, 3.0], [56.6, 3.0], [56.7, 3.0], [56.8, 3.0], [56.9, 3.0], [57.0, 3.0], [57.1, 3.0], [57.2, 3.0], [57.3, 3.0], [57.4, 3.0], [57.5, 3.0], [57.6, 3.0], [57.7, 3.0], [57.8, 3.0], [57.9, 3.0], [58.0, 3.0], [58.1, 3.0], [58.2, 3.0], [58.3, 3.0], [58.4, 3.0], [58.5, 4.0], [58.6, 4.0], [58.7, 4.0], [58.8, 4.0], [58.9, 4.0], [59.0, 4.0], [59.1, 4.0], [59.2, 4.0], [59.3, 4.0], [59.4, 4.0], [59.5, 4.0], [59.6, 4.0], [59.7, 4.0], [59.8, 4.0], [59.9, 4.0], [60.0, 4.0], [60.1, 4.0], [60.2, 4.0], [60.3, 4.0], [60.4, 4.0], [60.5, 4.0], [60.6, 4.0], [60.7, 4.0], [60.8, 4.0], [60.9, 4.0], [61.0, 4.0], [61.1, 4.0], [61.2, 4.0], [61.3, 4.0], [61.4, 4.0], [61.5, 4.0], [61.6, 4.0], [61.7, 4.0], [61.8, 4.0], [61.9, 4.0], [62.0, 4.0], [62.1, 4.0], [62.2, 4.0], [62.3, 4.0], [62.4, 4.0], [62.5, 4.0], [62.6, 4.0], [62.7, 4.0], [62.8, 4.0], [62.9, 4.0], [63.0, 4.0], [63.1, 4.0], [63.2, 4.0], [63.3, 4.0], [63.4, 4.0], [63.5, 4.0], [63.6, 4.0], [63.7, 4.0], [63.8, 4.0], [63.9, 4.0], [64.0, 4.0], [64.1, 4.0], [64.2, 4.0], [64.3, 4.0], [64.4, 4.0], [64.5, 4.0], [64.6, 4.0], [64.7, 4.0], [64.8, 4.0], [64.9, 4.0], [65.0, 4.0], [65.1, 4.0], [65.2, 4.0], [65.3, 4.0], [65.4, 4.0], [65.5, 4.0], [65.6, 4.0], [65.7, 4.0], [65.8, 4.0], [65.9, 4.0], [66.0, 4.0], [66.1, 4.0], [66.2, 4.0], [66.3, 4.0], [66.4, 4.0], [66.5, 4.0], [66.6, 4.0], [66.7, 4.0], [66.8, 4.0], [66.9, 4.0], [67.0, 4.0], [67.1, 4.0], [67.2, 4.0], [67.3, 4.0], [67.4, 4.0], [67.5, 4.0], [67.6, 4.0], [67.7, 4.0], [67.8, 4.0], [67.9, 4.0], [68.0, 4.0], [68.1, 4.0], [68.2, 4.0], [68.3, 5.0], [68.4, 5.0], [68.5, 5.0], [68.6, 5.0], [68.7, 5.0], [68.8, 5.0], [68.9, 5.0], [69.0, 5.0], [69.1, 5.0], [69.2, 5.0], [69.3, 5.0], [69.4, 5.0], [69.5, 5.0], [69.6, 5.0], [69.7, 5.0], [69.8, 5.0], [69.9, 5.0], [70.0, 5.0], [70.1, 5.0], [70.2, 5.0], [70.3, 5.0], [70.4, 5.0], [70.5, 5.0], [70.6, 5.0], [70.7, 5.0], [70.8, 5.0], [70.9, 5.0], [71.0, 5.0], [71.1, 5.0], [71.2, 5.0], [71.3, 5.0], [71.4, 5.0], [71.5, 5.0], [71.6, 5.0], [71.7, 5.0], [71.8, 5.0], [71.9, 5.0], [72.0, 5.0], [72.1, 5.0], [72.2, 5.0], [72.3, 5.0], [72.4, 5.0], [72.5, 5.0], [72.6, 5.0], [72.7, 5.0], [72.8, 5.0], [72.9, 5.0], [73.0, 5.0], [73.1, 5.0], [73.2, 5.0], [73.3, 5.0], [73.4, 5.0], [73.5, 5.0], [73.6, 5.0], [73.7, 5.0], [73.8, 5.0], [73.9, 5.0], [74.0, 5.0], [74.1, 5.0], [74.2, 5.0], [74.3, 5.0], [74.4, 5.0], [74.5, 5.0], [74.6, 6.0], [74.7, 6.0], [74.8, 6.0], [74.9, 6.0], [75.0, 6.0], [75.1, 6.0], [75.2, 6.0], [75.3, 6.0], [75.4, 6.0], [75.5, 6.0], [75.6, 6.0], [75.7, 6.0], [75.8, 6.0], [75.9, 6.0], [76.0, 6.0], [76.1, 6.0], [76.2, 6.0], [76.3, 6.0], [76.4, 6.0], [76.5, 6.0], [76.6, 6.0], [76.7, 6.0], [76.8, 6.0], [76.9, 6.0], [77.0, 6.0], [77.1, 6.0], [77.2, 6.0], [77.3, 6.0], [77.4, 6.0], [77.5, 6.0], [77.6, 6.0], [77.7, 6.0], [77.8, 6.0], [77.9, 6.0], [78.0, 6.0], [78.1, 6.0], [78.2, 6.0], [78.3, 6.0], [78.4, 6.0], [78.5, 6.0], [78.6, 6.0], [78.7, 6.0], [78.8, 7.0], [78.9, 7.0], [79.0, 7.0], [79.1, 7.0], [79.2, 7.0], [79.3, 7.0], [79.4, 7.0], [79.5, 7.0], [79.6, 7.0], [79.7, 7.0], [79.8, 7.0], [79.9, 7.0], [80.0, 7.0], [80.1, 7.0], [80.2, 7.0], [80.3, 7.0], [80.4, 7.0], [80.5, 7.0], [80.6, 7.0], [80.7, 7.0], [80.8, 7.0], [80.9, 7.0], [81.0, 7.0], [81.1, 7.0], [81.2, 7.0], [81.3, 7.0], [81.4, 7.0], [81.5, 7.0], [81.6, 7.0], [81.7, 7.0], [81.8, 7.0], [81.9, 7.0], [82.0, 7.0], [82.1, 8.0], [82.2, 8.0], [82.3, 8.0], [82.4, 8.0], [82.5, 8.0], [82.6, 8.0], [82.7, 8.0], [82.8, 8.0], [82.9, 8.0], [83.0, 8.0], [83.1, 8.0], [83.2, 8.0], [83.3, 8.0], [83.4, 8.0], [83.5, 8.0], [83.6, 8.0], [83.7, 8.0], [83.8, 8.0], [83.9, 8.0], [84.0, 8.0], [84.1, 8.0], [84.2, 8.0], [84.3, 8.0], [84.4, 9.0], [84.5, 9.0], [84.6, 9.0], [84.7, 9.0], [84.8, 9.0], [84.9, 9.0], [85.0, 9.0], [85.1, 9.0], [85.2, 9.0], [85.3, 9.0], [85.4, 9.0], [85.5, 9.0], [85.6, 9.0], [85.7, 9.0], [85.8, 10.0], [85.9, 10.0], [86.0, 10.0], [86.1, 10.0], [86.2, 10.0], [86.3, 10.0], [86.4, 10.0], [86.5, 10.0], [86.6, 10.0], [86.7, 10.0], [86.8, 10.0], [86.9, 10.0], [87.0, 11.0], [87.1, 11.0], [87.2, 11.0], [87.3, 11.0], [87.4, 11.0], [87.5, 11.0], [87.6, 11.0], [87.7, 12.0], [87.8, 12.0], [87.9, 12.0], [88.0, 12.0], [88.1, 12.0], [88.2, 12.0], [88.3, 12.0], [88.4, 13.0], [88.5, 13.0], [88.6, 13.0], [88.7, 13.0], [88.8, 13.0], [88.9, 14.0], [89.0, 14.0], [89.1, 14.0], [89.2, 14.0], [89.3, 14.0], [89.4, 15.0], [89.5, 15.0], [89.6, 15.0], [89.7, 15.0], [89.8, 16.0], [89.9, 16.0], [90.0, 16.0], [90.1, 16.0], [90.2, 16.0], [90.3, 17.0], [90.4, 17.0], [90.5, 17.0], [90.6, 17.0], [90.7, 18.0], [90.8, 18.0], [90.9, 18.0], [91.0, 18.0], [91.1, 19.0], [91.2, 19.0], [91.3, 19.0], [91.4, 19.0], [91.5, 20.0], [91.6, 20.0], [91.7, 20.0], [91.8, 20.0], [91.9, 21.0], [92.0, 21.0], [92.1, 21.0], [92.2, 22.0], [92.3, 22.0], [92.4, 22.0], [92.5, 23.0], [92.6, 23.0], [92.7, 24.0], [92.8, 24.0], [92.9, 25.0], [93.0, 25.0], [93.1, 26.0], [93.2, 26.0], [93.3, 27.0], [93.4, 28.0], [93.5, 29.0], [93.6, 30.0], [93.7, 31.0], [93.8, 32.0], [93.9, 33.0], [94.0, 34.0], [94.1, 35.0], [94.2, 36.0], [94.3, 37.0], [94.4, 38.0], [94.5, 39.0], [94.6, 39.0], [94.7, 40.0], [94.8, 40.0], [94.9, 41.0], [95.0, 41.0], [95.1, 41.0], [95.2, 42.0], [95.3, 43.0], [95.4, 44.0], [95.5, 44.0], [95.6, 45.0], [95.7, 47.0], [95.8, 48.0], [95.9, 49.0], [96.0, 50.0], [96.1, 50.0], [96.2, 52.0], [96.3, 53.0], [96.4, 54.0], [96.5, 55.0], [96.6, 57.0], [96.7, 58.0], [96.8, 59.0], [96.9, 61.0], [97.0, 62.0], [97.1, 63.0], [97.2, 64.0], [97.3, 65.0], [97.4, 66.0], [97.5, 67.0], [97.6, 67.0], [97.7, 68.0], [97.8, 70.0], [97.9, 70.0], [98.0, 71.0], [98.1, 72.0], [98.2, 73.0], [98.3, 74.0], [98.4, 76.0], [98.5, 77.0], [98.6, 80.0], [98.7, 81.0], [98.8, 82.0], [98.9, 85.0], [99.0, 86.0], [99.1, 89.0], [99.2, 92.0], [99.3, 96.0], [99.4, 101.0], [99.5, 104.0], [99.6, 106.0], [99.7, 108.0], [99.8, 112.0], [99.9, 116.0], [100.0, 131.0]], "isOverall": false, "label": "order", "isController": false}], "supportsControllersDiscrimination": true, "maxX": 100.0, "title": "Response Time Percentiles"}},
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
        data: {"result": {"minY": 51.0, "minX": 0.0, "maxY": 7949.0, "series": [{"data": [[0.0, 7949.0], [100.0, 51.0]], "isOverall": false, "label": "order", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 100, "maxX": 100.0, "title": "Response Time Distribution"}},
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
        data: {"result": {"minY": 5.0, "minX": 0.0, "ticks": [[0, "Requests having \nresponse time <= 500ms"], [1, "Requests having \nresponse time > 500ms and <= 1,500ms"], [2, "Requests having \nresponse time > 1,500ms"], [3, "Requests in error"]], "maxY": 7995.0, "series": [{"data": [[0.0, 7995.0]], "color": "#9ACD32", "isOverall": false, "label": "Requests having \nresponse time <= 500ms", "isController": false}, {"data": [], "color": "yellow", "isOverall": false, "label": "Requests having \nresponse time > 500ms and <= 1,500ms", "isController": false}, {"data": [], "color": "orange", "isOverall": false, "label": "Requests having \nresponse time > 1,500ms", "isController": false}, {"data": [[3.0, 5.0]], "color": "#FF6347", "isOverall": false, "label": "Requests in error", "isController": false}], "supportsControllersDiscrimination": false, "maxX": 3.0, "title": "Synthetic Response Times Distribution"}},
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
        data: {"result": {"minY": 3.335394126738794, "minX": 1.734094137E12, "maxY": 61.77777777777778, "series": [{"data": [[1.734094138E12, 4.769461077844316], [1.734094137E12, 61.77777777777778], [1.734094145E12, 4.4878378378378345], [1.734094144E12, 33.84439685938617], [1.734094143E12, 13.010504201680682], [1.734094142E12, 7.378911564625839], [1.734094141E12, 7.973118279569902], [1.73409414E12, 11.915106117353318], [1.734094139E12, 3.335394126738794]], "isOverall": false, "label": "线程组", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.734094145E12, "title": "Active Threads Over Time"}},
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
        data: {"result": {"minY": 2.6987951807228936, "minX": 1.0, "maxY": 107.33333333333333, "series": [{"data": [[2.0, 2.7419786096256686], [3.0, 2.7972575905974524], [4.0, 2.6987951807228936], [5.0, 2.9544334975369475], [6.0, 3.6528925619834722], [7.0, 3.8672376873661687], [8.0, 4.789325842696629], [9.0, 5.054607508532423], [10.0, 6.1125], [11.0, 7.834254143646407], [12.0, 7.280000000000001], [13.0, 6.6752136752136755], [14.0, 6.508333333333333], [15.0, 6.69047619047619], [16.0, 7.309278350515464], [17.0, 7.445945945945945], [18.0, 6.782608695652172], [19.0, 6.571428571428571], [20.0, 4.46451612903226], [21.0, 5.684210526315789], [22.0, 7.999999999999999], [23.0, 10.88888888888889], [24.0, 15.0], [25.0, 17.083333333333332], [26.0, 19.54166666666667], [27.0, 17.933333333333334], [28.0, 20.555555555555557], [29.0, 20.58823529411765], [30.0, 22.210526315789473], [31.0, 22.736842105263158], [33.0, 28.874999999999996], [32.0, 25.0], [35.0, 21.352941176470587], [34.0, 22.88235294117647], [37.0, 21.1875], [36.0, 21.307692307692307], [39.0, 21.33333333333333], [38.0, 18.444444444444446], [41.0, 19.842105263157894], [40.0, 18.809523809523807], [43.0, 24.6875], [42.0, 23.210526315789476], [44.0, 25.38461538461538], [45.0, 28.333333333333332], [47.0, 20.666666666666668], [46.0, 25.999999999999996], [49.0, 37.75000000000001], [48.0, 22.0], [51.0, 34.0], [50.0, 48.1], [52.0, 35.81818181818182], [53.0, 32.90909090909091], [54.0, 31.11111111111111], [55.0, 37.833333333333336], [57.0, 31.25], [56.0, 35.66666666666667], [59.0, 48.25], [58.0, 44.857142857142854], [61.0, 57.035714285714285], [60.0, 45.16666666666667], [62.0, 62.621621621621635], [63.0, 66.80000000000001], [66.0, 23.875], [64.0, 24.833333333333332], [65.0, 44.375], [67.0, 49.0], [71.0, 65.66666666666666], [70.0, 40.333333333333336], [69.0, 58.5], [68.0, 36.5], [72.0, 36.8], [73.0, 59.0], [75.0, 59.0], [74.0, 73.0], [77.0, 45.0], [76.0, 35.5], [79.0, 104.0], [78.0, 99.0], [83.0, 62.0], [82.0, 62.0], [81.0, 93.0], [80.0, 75.0], [87.0, 73.0], [86.0, 79.33333333333333], [85.0, 47.0], [84.0, 94.0], [91.0, 64.5], [90.0, 56.333333333333336], [89.0, 68.83333333333333], [88.0, 70.0], [93.0, 88.0], [92.0, 50.0], [94.0, 78.0], [99.0, 72.0], [98.0, 71.0], [97.0, 69.0], [96.0, 83.0], [103.0, 53.0], [102.0, 95.5], [101.0, 67.0], [100.0, 75.0], [106.0, 69.5], [105.0, 76.33333333333333], [104.0, 70.0], [109.0, 57.5], [111.0, 48.8], [110.0, 66.5], [108.0, 97.0], [112.0, 40.0], [115.0, 62.2], [114.0, 63.0], [113.0, 64.83333333333333], [118.0, 54.75], [117.0, 59.2], [116.0, 52.5], [119.0, 86.5], [122.0, 54.0], [123.0, 36.5], [121.0, 107.33333333333333], [120.0, 70.0], [127.0, 55.0], [126.0, 76.2], [125.0, 66.5], [124.0, 54.0], [128.0, 54.0], [129.0, 63.71428571428571], [135.0, 83.66666666666667], [134.0, 63.666666666666664], [133.0, 69.0], [130.0, 79.33333333333333], [132.0, 49.5], [131.0, 72.66666666666667], [141.0, 72.0], [143.0, 68.66666666666667], [140.0, 56.0], [139.0, 83.66666666666667], [138.0, 70.0], [136.0, 85.0], [142.0, 70.0], [137.0, 73.0], [151.0, 78.5], [150.0, 83.5], [149.0, 73.0], [147.0, 40.0], [146.0, 94.0], [144.0, 85.5], [148.0, 94.66666666666667], [145.0, 83.0], [159.0, 47.666666666666664], [158.0, 79.75], [157.0, 40.0], [156.0, 81.33333333333333], [155.0, 72.0], [154.0, 78.33333333333333], [153.0, 95.5], [152.0, 72.0], [163.0, 94.0], [162.0, 64.0], [161.0, 76.57142857142857], [160.0, 76.33333333333333], [164.0, 96.66666666666667], [1.0, 2.96678966789668]], "isOverall": false, "label": "order", "isController": false}, {"data": [[13.281124999999946, 8.078374999999998]], "isOverall": false, "label": "order-Aggregated", "isController": false}], "supportsControllersDiscrimination": true, "maxX": 164.0, "title": "Time VS Threads"}},
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
        data : {"result": {"minY": 12389.0, "minX": 1.734094137E12, "maxY": 997104.0, "series": [{"data": [[1.734094138E12, 226591.0], [1.734094137E12, 42322.0], [1.734094145E12, 502240.0], [1.734094144E12, 950213.0], [1.734094143E12, 968562.0], [1.734094142E12, 997104.0], [1.734094141E12, 757324.0], [1.73409414E12, 543094.0], [1.734094139E12, 439065.0]], "isOverall": false, "label": "Bytes received per second", "isController": false}, {"data": [[1.734094138E12, 65798.0], [1.734094137E12, 12389.0], [1.734094145E12, 145780.0], [1.734094144E12, 275975.0], [1.734094143E12, 281294.0], [1.734094142E12, 289568.0], [1.734094141E12, 219852.0], [1.73409414E12, 157775.0], [1.734094139E12, 127459.0]], "isOverall": false, "label": "Bytes sent per second", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.734094145E12, "title": "Bytes Throughput Over Time"}},
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
        data: {"result": {"minY": 3.1452859350850098, "minX": 1.734094137E12, "maxY": 63.17460317460319, "series": [{"data": [[1.734094138E12, 5.122754491017963], [1.734094137E12, 63.17460317460319], [1.734094145E12, 3.3108108108108123], [1.734094144E12, 21.38615274803709], [1.734094143E12, 7.031512605042008], [1.734094142E12, 3.744217687074827], [1.734094141E12, 5.586021505376344], [1.73409414E12, 3.3832709113607984], [1.734094139E12, 3.1452859350850098]], "isOverall": false, "label": "order", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.734094145E12, "title": "Response Time Over Time"}},
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
        data: {"result": {"minY": 3.115919629057187, "minX": 1.734094137E12, "maxY": 63.063492063492056, "series": [{"data": [[1.734094138E12, 5.03892215568862], [1.734094137E12, 63.063492063492056], [1.734094145E12, 3.293243243243246], [1.734094144E12, 21.356887937187736], [1.734094143E12, 7.013305322128853], [1.734094142E12, 3.7231292517006813], [1.734094141E12, 5.547491039426525], [1.73409414E12, 3.3595505617977515], [1.734094139E12, 3.115919629057187]], "isOverall": false, "label": "order", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.734094145E12, "title": "Latencies Over Time"}},
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
        data: {"result": {"minY": 0.5081081081081079, "minX": 1.734094137E12, "maxY": 36.57142857142858, "series": [{"data": [[1.734094138E12, 1.8922155688622737], [1.734094137E12, 36.57142857142858], [1.734094145E12, 0.5081081081081079], [1.734094144E12, 0.6138472519628847], [1.734094143E12, 0.5735294117647061], [1.734094142E12, 0.58843537414966], [1.734094141E12, 1.0062724014336932], [1.73409414E12, 0.9900124843945072], [1.734094139E12, 1.0695517774343113]], "isOverall": false, "label": "order", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.734094145E12, "title": "Connect Time Over Time"}},
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
        data: {"result": {"minY": 1.0, "minX": 1.734094137E12, "maxY": 131.0, "series": [{"data": [[1.734094138E12, 30.0], [1.734094137E12, 98.0], [1.734094145E12, 21.0], [1.734094144E12, 131.0], [1.734094143E12, 74.0], [1.734094142E12, 21.0], [1.734094141E12, 106.0], [1.73409414E12, 24.0], [1.734094139E12, 18.0]], "isOverall": false, "label": "Max", "isController": false}, {"data": [[1.734094138E12, 10.5], [1.734094137E12, 81.7], [1.734094145E12, 6.0], [1.734094144E12, 70.0], [1.734094143E12, 12.0], [1.734094142E12, 7.0], [1.734094141E12, 10.0], [1.73409414E12, 6.0], [1.734094139E12, 5.0]], "isOverall": false, "label": "90th percentile", "isController": false}, {"data": [[1.734094138E12, 24.0], [1.734094137E12, 98.0], [1.734094145E12, 20.0], [1.734094144E12, 112.99000000000001], [1.734094143E12, 55.440000000000055], [1.734094142E12, 13.0], [1.734094141E12, 47.0], [1.73409414E12, 13.0], [1.734094139E12, 13.519999999999982]], "isOverall": false, "label": "99th percentile", "isController": false}, {"data": [[1.734094138E12, 17.0], [1.734094137E12, 94.64999999999995], [1.734094145E12, 16.0], [1.734094144E12, 87.0], [1.734094143E12, 36.0], [1.734094142E12, 8.0], [1.734094141E12, 21.149999999999864], [1.73409414E12, 8.0], [1.734094139E12, 9.0]], "isOverall": false, "label": "95th percentile", "isController": false}, {"data": [[1.734094138E12, 1.0], [1.734094137E12, 5.0], [1.734094145E12, 1.0], [1.734094144E12, 1.0], [1.734094143E12, 1.0], [1.734094142E12, 1.0], [1.734094141E12, 1.0], [1.73409414E12, 1.0], [1.734094139E12, 1.0]], "isOverall": false, "label": "Min", "isController": false}, {"data": [[1.734094138E12, 3.0], [1.734094137E12, 67.0], [1.734094145E12, 2.0], [1.734094144E12, 7.0], [1.734094143E12, 4.0], [1.734094142E12, 3.0], [1.734094141E12, 3.0], [1.73409414E12, 3.0], [1.734094139E12, 2.0]], "isOverall": false, "label": "Median", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.734094145E12, "title": "Response Time Percentiles Over Time (successful requests only)"}},
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
    data: {"result": {"minY": 2.0, "minX": 63.0, "maxY": 83.0, "series": [{"data": [[1116.0, 3.0], [334.0, 3.0], [647.0, 2.0], [1401.0, 7.0], [1470.0, 3.0], [1428.0, 4.0], [740.0, 2.0], [801.0, 3.0], [63.0, 67.0]], "isOverall": false, "label": "Successes", "isController": false}, {"data": [[1401.0, 64.0], [1470.0, 28.0], [1428.0, 7.0], [801.0, 7.0], [63.0, 83.0]], "isOverall": false, "label": "Failures", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1470.0, "title": "Response Time Vs Request"}},
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
    data: {"result": {"minY": 2.0, "minX": 63.0, "maxY": 82.0, "series": [{"data": [[1116.0, 3.0], [334.0, 3.0], [647.0, 2.0], [1401.0, 7.0], [1470.0, 3.0], [1428.0, 4.0], [740.0, 2.0], [801.0, 3.0], [63.0, 67.0]], "isOverall": false, "label": "Successes", "isController": false}, {"data": [[1401.0, 64.0], [1470.0, 28.0], [1428.0, 7.0], [801.0, 6.0], [63.0, 82.0]], "isOverall": false, "label": "Failures", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1470.0, "title": "Latencies Vs Request"}},
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
        data: {"result": {"minY": 64.0, "minX": 1.734094137E12, "maxY": 1512.0, "series": [{"data": [[1.734094138E12, 336.0], [1.734094137E12, 64.0], [1.734094145E12, 704.0], [1.734094144E12, 1352.0], [1.734094143E12, 1512.0], [1.734094142E12, 1470.0], [1.734094141E12, 1114.0], [1.73409414E12, 801.0], [1.734094139E12, 647.0]], "isOverall": false, "label": "hitsPerSecond", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.734094145E12, "title": "Hits Per Second"}},
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
        data: {"result": {"minY": 1.0, "minX": 1.734094137E12, "maxY": 1469.0, "series": [{"data": [[1.734094138E12, 334.0], [1.734094137E12, 62.0], [1.734094145E12, 740.0], [1.734094144E12, 1400.0], [1.734094143E12, 1427.0], [1.734094142E12, 1469.0], [1.734094141E12, 1116.0], [1.73409414E12, 800.0], [1.734094139E12, 647.0]], "isOverall": false, "label": "200", "isController": false}, {"data": [[1.734094137E12, 1.0], [1.734094144E12, 1.0], [1.734094143E12, 1.0], [1.734094142E12, 1.0], [1.73409414E12, 1.0]], "isOverall": false, "label": "500", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.734094145E12, "title": "Codes Per Second"}},
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
        data: {"result": {"minY": 1.0, "minX": 1.734094137E12, "maxY": 1469.0, "series": [{"data": [[1.734094138E12, 334.0], [1.734094137E12, 62.0], [1.734094145E12, 740.0], [1.734094144E12, 1400.0], [1.734094143E12, 1427.0], [1.734094142E12, 1469.0], [1.734094141E12, 1116.0], [1.73409414E12, 800.0], [1.734094139E12, 647.0]], "isOverall": false, "label": "order-success", "isController": false}, {"data": [[1.734094137E12, 1.0], [1.734094144E12, 1.0], [1.734094143E12, 1.0], [1.734094142E12, 1.0], [1.73409414E12, 1.0]], "isOverall": false, "label": "order-failure", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.734094145E12, "title": "Transactions Per Second"}},
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
        data: {"result": {"minY": 1.0, "minX": 1.734094137E12, "maxY": 1469.0, "series": [{"data": [[1.734094138E12, 334.0], [1.734094137E12, 62.0], [1.734094145E12, 740.0], [1.734094144E12, 1400.0], [1.734094143E12, 1427.0], [1.734094142E12, 1469.0], [1.734094141E12, 1116.0], [1.73409414E12, 800.0], [1.734094139E12, 647.0]], "isOverall": false, "label": "Transaction-success", "isController": false}, {"data": [[1.734094137E12, 1.0], [1.734094144E12, 1.0], [1.734094143E12, 1.0], [1.734094142E12, 1.0], [1.73409414E12, 1.0]], "isOverall": false, "label": "Transaction-failure", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.734094145E12, "title": "Total Transactions Per Second"}},
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

