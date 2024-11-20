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
        data: {"result": {"minY": 6.0, "minX": 0.0, "maxY": 41.0, "series": [{"data": [[0.0, 6.0], [0.1, 6.0], [0.2, 6.0], [0.3, 6.0], [0.4, 6.0], [0.5, 6.0], [0.6, 6.0], [0.7, 6.0], [0.8, 6.0], [0.9, 6.0], [1.0, 6.0], [1.1, 7.0], [1.2, 7.0], [1.3, 7.0], [1.4, 7.0], [1.5, 7.0], [1.6, 7.0], [1.7, 7.0], [1.8, 7.0], [1.9, 7.0], [2.0, 7.0], [2.1, 7.0], [2.2, 7.0], [2.3, 7.0], [2.4, 7.0], [2.5, 7.0], [2.6, 7.0], [2.7, 7.0], [2.8, 7.0], [2.9, 7.0], [3.0, 7.0], [3.1, 7.0], [3.2, 7.0], [3.3, 7.0], [3.4, 7.0], [3.5, 7.0], [3.6, 7.0], [3.7, 7.0], [3.8, 7.0], [3.9, 7.0], [4.0, 7.0], [4.1, 7.0], [4.2, 7.0], [4.3, 7.0], [4.4, 7.0], [4.5, 7.0], [4.6, 7.0], [4.7, 7.0], [4.8, 7.0], [4.9, 7.0], [5.0, 7.0], [5.1, 7.0], [5.2, 7.0], [5.3, 7.0], [5.4, 7.0], [5.5, 7.0], [5.6, 7.0], [5.7, 7.0], [5.8, 7.0], [5.9, 7.0], [6.0, 7.0], [6.1, 7.0], [6.2, 7.0], [6.3, 7.0], [6.4, 7.0], [6.5, 7.0], [6.6, 7.0], [6.7, 7.0], [6.8, 7.0], [6.9, 7.0], [7.0, 8.0], [7.1, 8.0], [7.2, 8.0], [7.3, 8.0], [7.4, 8.0], [7.5, 8.0], [7.6, 8.0], [7.7, 8.0], [7.8, 8.0], [7.9, 8.0], [8.0, 8.0], [8.1, 8.0], [8.2, 8.0], [8.3, 8.0], [8.4, 8.0], [8.5, 8.0], [8.6, 8.0], [8.7, 8.0], [8.8, 8.0], [8.9, 8.0], [9.0, 8.0], [9.1, 8.0], [9.2, 8.0], [9.3, 8.0], [9.4, 8.0], [9.5, 8.0], [9.6, 8.0], [9.7, 8.0], [9.8, 8.0], [9.9, 9.0], [10.0, 9.0], [10.1, 9.0], [10.2, 9.0], [10.3, 9.0], [10.4, 9.0], [10.5, 9.0], [10.6, 9.0], [10.7, 10.0], [10.8, 10.0], [10.9, 12.0], [11.0, 12.0], [11.1, 12.0], [11.2, 12.0], [11.3, 12.0], [11.4, 12.0], [11.5, 12.0], [11.6, 12.0], [11.7, 12.0], [11.8, 12.0], [11.9, 12.0], [12.0, 12.0], [12.1, 12.0], [12.2, 12.0], [12.3, 12.0], [12.4, 12.0], [12.5, 12.0], [12.6, 12.0], [12.7, 12.0], [12.8, 12.0], [12.9, 12.0], [13.0, 12.0], [13.1, 12.0], [13.2, 12.0], [13.3, 12.0], [13.4, 12.0], [13.5, 12.0], [13.6, 12.0], [13.7, 12.0], [13.8, 12.0], [13.9, 12.0], [14.0, 12.0], [14.1, 12.0], [14.2, 12.0], [14.3, 12.0], [14.4, 12.0], [14.5, 12.0], [14.6, 12.0], [14.7, 12.0], [14.8, 12.0], [14.9, 12.0], [15.0, 12.0], [15.1, 12.0], [15.2, 12.0], [15.3, 12.0], [15.4, 12.0], [15.5, 12.0], [15.6, 12.0], [15.7, 12.0], [15.8, 12.0], [15.9, 12.0], [16.0, 12.0], [16.1, 12.0], [16.2, 12.0], [16.3, 12.0], [16.4, 12.0], [16.5, 12.0], [16.6, 12.0], [16.7, 12.0], [16.8, 12.0], [16.9, 12.0], [17.0, 12.0], [17.1, 12.0], [17.2, 12.0], [17.3, 12.0], [17.4, 12.0], [17.5, 12.0], [17.6, 12.0], [17.7, 12.0], [17.8, 12.0], [17.9, 12.0], [18.0, 12.0], [18.1, 12.0], [18.2, 12.0], [18.3, 12.0], [18.4, 12.0], [18.5, 12.0], [18.6, 12.0], [18.7, 12.0], [18.8, 12.0], [18.9, 12.0], [19.0, 12.0], [19.1, 12.0], [19.2, 12.0], [19.3, 12.0], [19.4, 12.0], [19.5, 12.0], [19.6, 12.0], [19.7, 12.0], [19.8, 12.0], [19.9, 12.0], [20.0, 12.0], [20.1, 12.0], [20.2, 12.0], [20.3, 12.0], [20.4, 12.0], [20.5, 12.0], [20.6, 12.0], [20.7, 12.0], [20.8, 12.0], [20.9, 12.0], [21.0, 12.0], [21.1, 12.0], [21.2, 12.0], [21.3, 12.0], [21.4, 12.0], [21.5, 12.0], [21.6, 12.0], [21.7, 12.0], [21.8, 12.0], [21.9, 12.0], [22.0, 12.0], [22.1, 12.0], [22.2, 12.0], [22.3, 12.0], [22.4, 12.0], [22.5, 12.0], [22.6, 12.0], [22.7, 12.0], [22.8, 12.0], [22.9, 12.0], [23.0, 12.0], [23.1, 12.0], [23.2, 12.0], [23.3, 13.0], [23.4, 13.0], [23.5, 13.0], [23.6, 13.0], [23.7, 13.0], [23.8, 13.0], [23.9, 13.0], [24.0, 13.0], [24.1, 13.0], [24.2, 13.0], [24.3, 13.0], [24.4, 13.0], [24.5, 13.0], [24.6, 13.0], [24.7, 13.0], [24.8, 13.0], [24.9, 13.0], [25.0, 13.0], [25.1, 13.0], [25.2, 13.0], [25.3, 13.0], [25.4, 13.0], [25.5, 13.0], [25.6, 13.0], [25.7, 13.0], [25.8, 13.0], [25.9, 13.0], [26.0, 13.0], [26.1, 13.0], [26.2, 13.0], [26.3, 13.0], [26.4, 13.0], [26.5, 13.0], [26.6, 13.0], [26.7, 13.0], [26.8, 13.0], [26.9, 13.0], [27.0, 13.0], [27.1, 13.0], [27.2, 13.0], [27.3, 13.0], [27.4, 13.0], [27.5, 13.0], [27.6, 13.0], [27.7, 13.0], [27.8, 13.0], [27.9, 13.0], [28.0, 13.0], [28.1, 13.0], [28.2, 13.0], [28.3, 13.0], [28.4, 13.0], [28.5, 13.0], [28.6, 13.0], [28.7, 13.0], [28.8, 13.0], [28.9, 13.0], [29.0, 13.0], [29.1, 13.0], [29.2, 13.0], [29.3, 13.0], [29.4, 13.0], [29.5, 13.0], [29.6, 13.0], [29.7, 13.0], [29.8, 13.0], [29.9, 13.0], [30.0, 13.0], [30.1, 13.0], [30.2, 13.0], [30.3, 13.0], [30.4, 13.0], [30.5, 13.0], [30.6, 13.0], [30.7, 13.0], [30.8, 13.0], [30.9, 13.0], [31.0, 13.0], [31.1, 13.0], [31.2, 13.0], [31.3, 13.0], [31.4, 13.0], [31.5, 13.0], [31.6, 13.0], [31.7, 13.0], [31.8, 13.0], [31.9, 13.0], [32.0, 13.0], [32.1, 13.0], [32.2, 13.0], [32.3, 13.0], [32.4, 13.0], [32.5, 13.0], [32.6, 13.0], [32.7, 13.0], [32.8, 13.0], [32.9, 13.0], [33.0, 13.0], [33.1, 13.0], [33.2, 13.0], [33.3, 13.0], [33.4, 13.0], [33.5, 13.0], [33.6, 13.0], [33.7, 13.0], [33.8, 13.0], [33.9, 13.0], [34.0, 13.0], [34.1, 13.0], [34.2, 13.0], [34.3, 13.0], [34.4, 13.0], [34.5, 13.0], [34.6, 13.0], [34.7, 13.0], [34.8, 13.0], [34.9, 13.0], [35.0, 13.0], [35.1, 13.0], [35.2, 13.0], [35.3, 13.0], [35.4, 13.0], [35.5, 13.0], [35.6, 13.0], [35.7, 13.0], [35.8, 13.0], [35.9, 13.0], [36.0, 13.0], [36.1, 13.0], [36.2, 13.0], [36.3, 13.0], [36.4, 13.0], [36.5, 13.0], [36.6, 13.0], [36.7, 13.0], [36.8, 13.0], [36.9, 13.0], [37.0, 13.0], [37.1, 13.0], [37.2, 13.0], [37.3, 13.0], [37.4, 13.0], [37.5, 13.0], [37.6, 13.0], [37.7, 13.0], [37.8, 13.0], [37.9, 13.0], [38.0, 13.0], [38.1, 13.0], [38.2, 13.0], [38.3, 13.0], [38.4, 13.0], [38.5, 13.0], [38.6, 13.0], [38.7, 13.0], [38.8, 13.0], [38.9, 13.0], [39.0, 13.0], [39.1, 13.0], [39.2, 13.0], [39.3, 13.0], [39.4, 13.0], [39.5, 13.0], [39.6, 13.0], [39.7, 13.0], [39.8, 13.0], [39.9, 13.0], [40.0, 13.0], [40.1, 13.0], [40.2, 13.0], [40.3, 13.0], [40.4, 13.0], [40.5, 13.0], [40.6, 13.0], [40.7, 13.0], [40.8, 13.0], [40.9, 13.0], [41.0, 13.0], [41.1, 13.0], [41.2, 13.0], [41.3, 13.0], [41.4, 13.0], [41.5, 13.0], [41.6, 13.0], [41.7, 13.0], [41.8, 13.0], [41.9, 13.0], [42.0, 13.0], [42.1, 13.0], [42.2, 13.0], [42.3, 13.0], [42.4, 13.0], [42.5, 13.0], [42.6, 13.0], [42.7, 13.0], [42.8, 13.0], [42.9, 13.0], [43.0, 13.0], [43.1, 13.0], [43.2, 13.0], [43.3, 13.0], [43.4, 13.0], [43.5, 13.0], [43.6, 13.0], [43.7, 13.0], [43.8, 13.0], [43.9, 13.0], [44.0, 13.0], [44.1, 13.0], [44.2, 13.0], [44.3, 13.0], [44.4, 13.0], [44.5, 13.0], [44.6, 13.0], [44.7, 13.0], [44.8, 13.0], [44.9, 13.0], [45.0, 13.0], [45.1, 13.0], [45.2, 13.0], [45.3, 13.0], [45.4, 13.0], [45.5, 13.0], [45.6, 13.0], [45.7, 13.0], [45.8, 13.0], [45.9, 13.0], [46.0, 13.0], [46.1, 13.0], [46.2, 13.0], [46.3, 13.0], [46.4, 13.0], [46.5, 13.0], [46.6, 13.0], [46.7, 13.0], [46.8, 13.0], [46.9, 13.0], [47.0, 13.0], [47.1, 13.0], [47.2, 13.0], [47.3, 13.0], [47.4, 13.0], [47.5, 13.0], [47.6, 13.0], [47.7, 13.0], [47.8, 13.0], [47.9, 13.0], [48.0, 13.0], [48.1, 13.0], [48.2, 13.0], [48.3, 13.0], [48.4, 13.0], [48.5, 13.0], [48.6, 13.0], [48.7, 13.0], [48.8, 13.0], [48.9, 13.0], [49.0, 13.0], [49.1, 13.0], [49.2, 13.0], [49.3, 13.0], [49.4, 13.0], [49.5, 13.0], [49.6, 13.0], [49.7, 13.0], [49.8, 13.0], [49.9, 13.0], [50.0, 13.0], [50.1, 13.0], [50.2, 13.0], [50.3, 13.0], [50.4, 13.0], [50.5, 13.0], [50.6, 13.0], [50.7, 13.0], [50.8, 13.0], [50.9, 13.0], [51.0, 13.0], [51.1, 13.0], [51.2, 13.0], [51.3, 13.0], [51.4, 13.0], [51.5, 13.0], [51.6, 13.0], [51.7, 13.0], [51.8, 13.0], [51.9, 13.0], [52.0, 13.0], [52.1, 13.0], [52.2, 13.0], [52.3, 13.0], [52.4, 13.0], [52.5, 13.0], [52.6, 13.0], [52.7, 13.0], [52.8, 13.0], [52.9, 13.0], [53.0, 13.0], [53.1, 13.0], [53.2, 13.0], [53.3, 13.0], [53.4, 13.0], [53.5, 13.0], [53.6, 13.0], [53.7, 13.0], [53.8, 13.0], [53.9, 13.0], [54.0, 13.0], [54.1, 13.0], [54.2, 13.0], [54.3, 13.0], [54.4, 13.0], [54.5, 13.0], [54.6, 13.0], [54.7, 13.0], [54.8, 13.0], [54.9, 13.0], [55.0, 13.0], [55.1, 13.0], [55.2, 13.0], [55.3, 13.0], [55.4, 13.0], [55.5, 13.0], [55.6, 13.0], [55.7, 13.0], [55.8, 13.0], [55.9, 13.0], [56.0, 13.0], [56.1, 13.0], [56.2, 13.0], [56.3, 13.0], [56.4, 13.0], [56.5, 13.0], [56.6, 13.0], [56.7, 13.0], [56.8, 13.0], [56.9, 13.0], [57.0, 13.0], [57.1, 13.0], [57.2, 13.0], [57.3, 13.0], [57.4, 13.0], [57.5, 13.0], [57.6, 13.0], [57.7, 13.0], [57.8, 13.0], [57.9, 13.0], [58.0, 13.0], [58.1, 13.0], [58.2, 13.0], [58.3, 13.0], [58.4, 13.0], [58.5, 13.0], [58.6, 13.0], [58.7, 13.0], [58.8, 13.0], [58.9, 13.0], [59.0, 13.0], [59.1, 13.0], [59.2, 13.0], [59.3, 13.0], [59.4, 13.0], [59.5, 13.0], [59.6, 13.0], [59.7, 13.0], [59.8, 13.0], [59.9, 13.0], [60.0, 13.0], [60.1, 13.0], [60.2, 13.0], [60.3, 13.0], [60.4, 13.0], [60.5, 13.0], [60.6, 13.0], [60.7, 13.0], [60.8, 13.0], [60.9, 13.0], [61.0, 13.0], [61.1, 13.0], [61.2, 13.0], [61.3, 13.0], [61.4, 13.0], [61.5, 13.0], [61.6, 13.0], [61.7, 13.0], [61.8, 13.0], [61.9, 13.0], [62.0, 13.0], [62.1, 13.0], [62.2, 13.0], [62.3, 13.0], [62.4, 13.0], [62.5, 13.0], [62.6, 13.0], [62.7, 13.0], [62.8, 13.0], [62.9, 13.0], [63.0, 13.0], [63.1, 13.0], [63.2, 13.0], [63.3, 13.0], [63.4, 13.0], [63.5, 13.0], [63.6, 13.0], [63.7, 13.0], [63.8, 13.0], [63.9, 13.0], [64.0, 13.0], [64.1, 13.0], [64.2, 13.0], [64.3, 13.0], [64.4, 13.0], [64.5, 13.0], [64.6, 13.0], [64.7, 13.0], [64.8, 13.0], [64.9, 13.0], [65.0, 13.0], [65.1, 13.0], [65.2, 13.0], [65.3, 13.0], [65.4, 13.0], [65.5, 13.0], [65.6, 13.0], [65.7, 13.0], [65.8, 13.0], [65.9, 13.0], [66.0, 13.0], [66.1, 13.0], [66.2, 13.0], [66.3, 13.0], [66.4, 13.0], [66.5, 13.0], [66.6, 13.0], [66.7, 13.0], [66.8, 13.0], [66.9, 13.0], [67.0, 13.0], [67.1, 13.0], [67.2, 13.0], [67.3, 13.0], [67.4, 13.0], [67.5, 13.0], [67.6, 13.0], [67.7, 13.0], [67.8, 13.0], [67.9, 13.0], [68.0, 13.0], [68.1, 13.0], [68.2, 13.0], [68.3, 13.0], [68.4, 13.0], [68.5, 13.0], [68.6, 13.0], [68.7, 13.0], [68.8, 13.0], [68.9, 13.0], [69.0, 13.0], [69.1, 13.0], [69.2, 13.0], [69.3, 13.0], [69.4, 13.0], [69.5, 13.0], [69.6, 13.0], [69.7, 13.0], [69.8, 13.0], [69.9, 13.0], [70.0, 13.0], [70.1, 13.0], [70.2, 13.0], [70.3, 13.0], [70.4, 13.0], [70.5, 13.0], [70.6, 13.0], [70.7, 13.0], [70.8, 13.0], [70.9, 13.0], [71.0, 13.0], [71.1, 13.0], [71.2, 13.0], [71.3, 13.0], [71.4, 13.0], [71.5, 13.0], [71.6, 13.0], [71.7, 13.0], [71.8, 13.0], [71.9, 13.0], [72.0, 13.0], [72.1, 13.0], [72.2, 13.0], [72.3, 13.0], [72.4, 13.0], [72.5, 13.0], [72.6, 13.0], [72.7, 13.0], [72.8, 13.0], [72.9, 13.0], [73.0, 13.0], [73.1, 13.0], [73.2, 13.0], [73.3, 13.0], [73.4, 13.0], [73.5, 13.0], [73.6, 13.0], [73.7, 13.0], [73.8, 13.0], [73.9, 13.0], [74.0, 13.0], [74.1, 13.0], [74.2, 13.0], [74.3, 13.0], [74.4, 13.0], [74.5, 13.0], [74.6, 13.0], [74.7, 13.0], [74.8, 13.0], [74.9, 13.0], [75.0, 13.0], [75.1, 13.0], [75.2, 13.0], [75.3, 13.0], [75.4, 13.0], [75.5, 13.0], [75.6, 13.0], [75.7, 13.0], [75.8, 13.0], [75.9, 13.0], [76.0, 13.0], [76.1, 13.0], [76.2, 13.0], [76.3, 13.0], [76.4, 13.0], [76.5, 13.0], [76.6, 13.0], [76.7, 13.0], [76.8, 13.0], [76.9, 13.0], [77.0, 13.0], [77.1, 13.0], [77.2, 13.0], [77.3, 13.0], [77.4, 13.0], [77.5, 13.0], [77.6, 13.0], [77.7, 13.0], [77.8, 13.0], [77.9, 13.0], [78.0, 13.0], [78.1, 13.0], [78.2, 13.0], [78.3, 13.0], [78.4, 13.0], [78.5, 13.0], [78.6, 13.0], [78.7, 13.0], [78.8, 13.0], [78.9, 13.0], [79.0, 13.0], [79.1, 13.0], [79.2, 13.0], [79.3, 13.0], [79.4, 13.0], [79.5, 13.0], [79.6, 14.0], [79.7, 14.0], [79.8, 14.0], [79.9, 14.0], [80.0, 14.0], [80.1, 14.0], [80.2, 14.0], [80.3, 14.0], [80.4, 14.0], [80.5, 14.0], [80.6, 14.0], [80.7, 14.0], [80.8, 14.0], [80.9, 14.0], [81.0, 14.0], [81.1, 14.0], [81.2, 14.0], [81.3, 14.0], [81.4, 14.0], [81.5, 14.0], [81.6, 14.0], [81.7, 14.0], [81.8, 14.0], [81.9, 14.0], [82.0, 14.0], [82.1, 14.0], [82.2, 14.0], [82.3, 14.0], [82.4, 14.0], [82.5, 14.0], [82.6, 14.0], [82.7, 14.0], [82.8, 14.0], [82.9, 14.0], [83.0, 14.0], [83.1, 14.0], [83.2, 14.0], [83.3, 14.0], [83.4, 14.0], [83.5, 14.0], [83.6, 14.0], [83.7, 14.0], [83.8, 14.0], [83.9, 14.0], [84.0, 14.0], [84.1, 14.0], [84.2, 14.0], [84.3, 14.0], [84.4, 14.0], [84.5, 14.0], [84.6, 14.0], [84.7, 14.0], [84.8, 14.0], [84.9, 14.0], [85.0, 14.0], [85.1, 14.0], [85.2, 14.0], [85.3, 14.0], [85.4, 14.0], [85.5, 14.0], [85.6, 14.0], [85.7, 14.0], [85.8, 14.0], [85.9, 14.0], [86.0, 14.0], [86.1, 14.0], [86.2, 14.0], [86.3, 14.0], [86.4, 14.0], [86.5, 14.0], [86.6, 14.0], [86.7, 14.0], [86.8, 14.0], [86.9, 14.0], [87.0, 14.0], [87.1, 14.0], [87.2, 14.0], [87.3, 14.0], [87.4, 14.0], [87.5, 14.0], [87.6, 14.0], [87.7, 14.0], [87.8, 14.0], [87.9, 14.0], [88.0, 14.0], [88.1, 14.0], [88.2, 14.0], [88.3, 14.0], [88.4, 14.0], [88.5, 14.0], [88.6, 14.0], [88.7, 14.0], [88.8, 14.0], [88.9, 14.0], [89.0, 14.0], [89.1, 14.0], [89.2, 14.0], [89.3, 14.0], [89.4, 14.0], [89.5, 14.0], [89.6, 14.0], [89.7, 14.0], [89.8, 14.0], [89.9, 14.0], [90.0, 14.0], [90.1, 14.0], [90.2, 14.0], [90.3, 14.0], [90.4, 14.0], [90.5, 14.0], [90.6, 14.0], [90.7, 14.0], [90.8, 14.0], [90.9, 14.0], [91.0, 14.0], [91.1, 14.0], [91.2, 14.0], [91.3, 14.0], [91.4, 14.0], [91.5, 14.0], [91.6, 14.0], [91.7, 14.0], [91.8, 14.0], [91.9, 14.0], [92.0, 14.0], [92.1, 14.0], [92.2, 14.0], [92.3, 14.0], [92.4, 14.0], [92.5, 14.0], [92.6, 14.0], [92.7, 14.0], [92.8, 14.0], [92.9, 14.0], [93.0, 14.0], [93.1, 14.0], [93.2, 14.0], [93.3, 14.0], [93.4, 14.0], [93.5, 14.0], [93.6, 14.0], [93.7, 14.0], [93.8, 14.0], [93.9, 14.0], [94.0, 14.0], [94.1, 14.0], [94.2, 14.0], [94.3, 14.0], [94.4, 14.0], [94.5, 14.0], [94.6, 15.0], [94.7, 15.0], [94.8, 15.0], [94.9, 15.0], [95.0, 15.0], [95.1, 15.0], [95.2, 15.0], [95.3, 15.0], [95.4, 15.0], [95.5, 15.0], [95.6, 15.0], [95.7, 15.0], [95.8, 15.0], [95.9, 15.0], [96.0, 15.0], [96.1, 15.0], [96.2, 15.0], [96.3, 15.0], [96.4, 15.0], [96.5, 15.0], [96.6, 15.0], [96.7, 15.0], [96.8, 15.0], [96.9, 15.0], [97.0, 15.0], [97.1, 15.0], [97.2, 15.0], [97.3, 15.0], [97.4, 15.0], [97.5, 15.0], [97.6, 15.0], [97.7, 15.0], [97.8, 15.0], [97.9, 15.0], [98.0, 15.0], [98.1, 15.0], [98.2, 15.0], [98.3, 15.0], [98.4, 15.0], [98.5, 15.0], [98.6, 15.0], [98.7, 15.0], [98.8, 15.0], [98.9, 15.0], [99.0, 16.0], [99.1, 16.0], [99.2, 16.0], [99.3, 16.0], [99.4, 16.0], [99.5, 16.0], [99.6, 16.0], [99.7, 17.0], [99.8, 17.0], [99.9, 18.0], [100.0, 41.0]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "maxX": 100.0, "title": "Response Time Percentiles"}},
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
        data: {"result": {"minY": 6000.0, "minX": 0.0, "maxY": 6000.0, "series": [{"data": [[0.0, 6000.0]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 100, "maxX": 4.9E-324, "title": "Response Time Distribution"}},
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
        data: {"result": {"minY": 657.0, "minX": 0.0, "ticks": [[0, "Requests having \nresponse time <= 500ms"], [1, "Requests having \nresponse time > 500ms and <= 1,500ms"], [2, "Requests having \nresponse time > 1,500ms"], [3, "Requests in error"]], "maxY": 5343.0, "series": [{"data": [[0.0, 5343.0]], "color": "#9ACD32", "isOverall": false, "label": "Requests having \nresponse time <= 500ms", "isController": false}, {"data": [], "color": "yellow", "isOverall": false, "label": "Requests having \nresponse time > 500ms and <= 1,500ms", "isController": false}, {"data": [], "color": "orange", "isOverall": false, "label": "Requests having \nresponse time > 1,500ms", "isController": false}, {"data": [[3.0, 657.0]], "color": "#FF6347", "isOverall": false, "label": "Requests in error", "isController": false}], "supportsControllersDiscrimination": false, "maxX": 3.0, "title": "Synthetic Response Times Distribution"}},
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
        data: {"result": {"minY": 1.0, "minX": 1.731747799E12, "maxY": 1.6744186046511629, "series": [{"data": [[1.731747843E12, 1.0], [1.731747886E12, 1.0], [1.731747845E12, 1.0], [1.731747888E12, 1.0], [1.731747802E12, 1.0149253731343284], [1.731747841E12, 1.0], [1.731747884E12, 1.0], [1.7317478E12, 1.0], [1.731747849E12, 1.0], [1.731747806E12, 1.0], [1.731747808E12, 1.0], [1.731747804E12, 1.0], [1.731747847E12, 1.0], [1.731747812E12, 1.0], [1.731747855E12, 1.0], [1.731747851E12, 1.0], [1.731747853E12, 1.0], [1.73174781E12, 1.0], [1.731747859E12, 1.0], [1.731747861E12, 1.0], [1.731747818E12, 1.0], [1.731747857E12, 1.0], [1.731747814E12, 1.0], [1.731747816E12, 1.0], [1.731747865E12, 1.0], [1.731747822E12, 1.0], [1.731747824E12, 1.0], [1.73174782E12, 1.0], [1.731747863E12, 1.0], [1.731747828E12, 1.0], [1.731747871E12, 1.0], [1.731747867E12, 1.0], [1.731747869E12, 1.0], [1.731747826E12, 1.0], [1.731747875E12, 1.0], [1.731747877E12, 1.0], [1.731747834E12, 1.0], [1.731747873E12, 1.0], [1.73174783E12, 1.0], [1.731747832E12, 1.0], [1.731747881E12, 1.0], [1.731747838E12, 1.0], [1.73174784E12, 1.0], [1.731747836E12, 1.0], [1.731747879E12, 1.0], [1.731747801E12, 1.0], [1.731747844E12, 1.0], [1.731747887E12, 1.0], [1.731747883E12, 1.0], [1.731747885E12, 1.0], [1.731747799E12, 1.6744186046511629], [1.731747842E12, 1.0], [1.731747807E12, 1.0], [1.73174785E12, 1.0], [1.731747889E12, 1.0], [1.731747803E12, 1.0], [1.731747846E12, 1.0], [1.731747805E12, 1.0], [1.731747848E12, 1.0], [1.731747811E12, 1.0], [1.731747854E12, 1.0], [1.731747813E12, 1.0], [1.731747856E12, 1.0], [1.731747809E12, 1.0], [1.731747852E12, 1.0], [1.731747817E12, 1.0], [1.73174786E12, 1.0], [1.731747815E12, 1.0], [1.731747858E12, 1.0], [1.731747823E12, 1.0], [1.731747866E12, 1.0], [1.731747819E12, 1.0], [1.731747862E12, 1.0], [1.731747821E12, 1.0], [1.731747864E12, 1.0], [1.731747827E12, 1.0], [1.73174787E12, 1.0], [1.731747829E12, 1.0], [1.731747872E12, 1.0], [1.731747825E12, 1.0], [1.731747868E12, 1.0], [1.731747833E12, 1.0], [1.731747876E12, 1.0], [1.731747831E12, 1.0], [1.731747874E12, 1.0], [1.731747839E12, 1.0], [1.731747882E12, 1.0], [1.731747835E12, 1.0], [1.731747878E12, 1.0], [1.731747837E12, 1.0], [1.73174788E12, 1.0]], "isOverall": false, "label": "线程组", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731747889E12, "title": "Active Threads Over Time"}},
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
        data: {"result": {"minY": 12.535510887772169, "minX": 1.0, "maxY": 14.533333333333335, "series": [{"data": [[1.0, 12.535510887772169], [2.0, 14.533333333333335]], "isOverall": false, "label": "Products", "isController": false}, {"data": [[1.004999999999998, 12.545500000000004]], "isOverall": false, "label": "Products-Aggregated", "isController": false}], "supportsControllersDiscrimination": true, "maxX": 2.0, "title": "Time VS Threads"}},
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
        data : {"result": {"minY": 5015.0, "minX": 1.731747799E12, "maxY": 111185.0, "series": [{"data": [[1.731747843E12, 99213.0], [1.731747886E12, 101781.0], [1.731747845E12, 97460.0], [1.731747888E12, 95318.0], [1.731747802E12, 109140.0], [1.731747841E12, 98240.0], [1.731747884E12, 96978.0], [1.7317478E12, 94022.0], [1.731747849E12, 93693.0], [1.731747806E12, 96578.0], [1.731747808E12, 93103.0], [1.731747804E12, 93066.0], [1.731747847E12, 102521.0], [1.731747812E12, 97835.0], [1.731747855E12, 109520.0], [1.731747851E12, 95178.0], [1.731747853E12, 92301.0], [1.73174781E12, 110027.0], [1.731747859E12, 96011.0], [1.731747861E12, 95863.0], [1.731747818E12, 99948.0], [1.731747857E12, 95340.0], [1.731747814E12, 91314.0], [1.731747816E12, 95517.0], [1.731747865E12, 90551.0], [1.731747822E12, 86583.0], [1.731747824E12, 95362.0], [1.73174782E12, 93237.0], [1.731747863E12, 101506.0], [1.731747828E12, 98950.0], [1.731747871E12, 97320.0], [1.731747867E12, 88172.0], [1.731747869E12, 92746.0], [1.731747826E12, 93062.0], [1.731747875E12, 95620.0], [1.731747877E12, 106503.0], [1.731747834E12, 97727.0], [1.731747873E12, 96716.0], [1.73174783E12, 97119.0], [1.731747832E12, 107009.0], [1.731747881E12, 100864.0], [1.731747838E12, 94791.0], [1.73174784E12, 105863.0], [1.731747836E12, 98847.0], [1.731747879E12, 99272.0], [1.731747801E12, 95517.0], [1.731747844E12, 90523.0], [1.731747887E12, 89693.0], [1.731747883E12, 92423.0], [1.731747885E12, 108193.0], [1.731747799E12, 58284.0], [1.731747842E12, 92220.0], [1.731747807E12, 93320.0], [1.73174785E12, 94808.0], [1.731747889E12, 30585.0], [1.731747803E12, 100175.0], [1.731747846E12, 94016.0], [1.731747805E12, 96823.0], [1.731747848E12, 103871.0], [1.731747811E12, 95470.0], [1.731747854E12, 98193.0], [1.731747813E12, 94716.0], [1.731747856E12, 95120.0], [1.731747809E12, 97532.0], [1.731747852E12, 96881.0], [1.731747817E12, 106737.0], [1.73174786E12, 91803.0], [1.731747815E12, 94022.0], [1.731747858E12, 93725.0], [1.731747823E12, 98030.0], [1.731747866E12, 102321.0], [1.731747819E12, 95443.0], [1.731747862E12, 102589.0], [1.731747821E12, 102227.0], [1.731747864E12, 99800.0], [1.731747827E12, 95562.0], [1.73174787E12, 111185.0], [1.731747829E12, 90326.0], [1.731747872E12, 93931.0], [1.731747825E12, 110535.0], [1.731747868E12, 98124.0], [1.731747833E12, 99383.0], [1.731747876E12, 90622.0], [1.731747831E12, 91728.0], [1.731747874E12, 92194.0], [1.731747839E12, 98854.0], [1.731747882E12, 92831.0], [1.731747835E12, 92071.0], [1.731747878E12, 98612.0], [1.731747837E12, 92421.0], [1.73174788E12, 92098.0]], "isOverall": false, "label": "Bytes received per second", "isController": false}, {"data": [[1.731747843E12, 15922.0], [1.731747886E12, 16401.0], [1.731747845E12, 16137.0], [1.731747888E12, 16103.0], [1.731747802E12, 16003.0], [1.731747841E12, 16476.0], [1.731747884E12, 15900.0], [1.7317478E12, 15711.0], [1.731747849E12, 15282.0], [1.731747806E12, 15715.0], [1.731747808E12, 15229.0], [1.731747804E12, 15732.0], [1.731747847E12, 15434.0], [1.731747812E12, 15978.0], [1.731747855E12, 16240.0], [1.731747851E12, 15409.0], [1.731747853E12, 15310.0], [1.73174781E12, 16144.0], [1.731747859E12, 16465.0], [1.731747861E12, 15466.0], [1.731747818E12, 15897.0], [1.731747857E12, 16197.0], [1.731747814E12, 15899.0], [1.731747816E12, 15680.0], [1.731747865E12, 15417.0], [1.731747822E12, 15414.0], [1.731747824E12, 15462.0], [1.73174782E12, 15377.0], [1.731747863E12, 16022.0], [1.731747828E12, 15967.0], [1.731747871E12, 15672.0], [1.731747867E12, 14789.0], [1.731747869E12, 15219.0], [1.731747826E12, 15459.0], [1.731747875E12, 16093.0], [1.731747877E12, 16152.0], [1.731747834E12, 15984.0], [1.731747873E12, 16099.0], [1.73174783E12, 16162.0], [1.731747832E12, 15927.0], [1.731747881E12, 16395.0], [1.731747838E12, 15508.0], [1.73174784E12, 15547.0], [1.731747836E12, 15931.0], [1.731747879E12, 16200.0], [1.731747801E12, 15680.0], [1.731747844E12, 15745.0], [1.731747887E12, 15023.0], [1.731747883E12, 15305.0], [1.731747885E12, 15649.0], [1.731747799E12, 10167.0], [1.731747842E12, 15033.0], [1.731747807E12, 16170.0], [1.73174785E12, 16097.0], [1.731747889E12, 5015.0], [1.731747803E12, 16113.0], [1.731747846E12, 15435.0], [1.731747805E12, 15638.0], [1.731747848E12, 16214.0], [1.731747811E12, 15720.0], [1.731747854E12, 15912.0], [1.731747813E12, 15211.0], [1.731747856E12, 15312.0], [1.731747809E12, 15891.0], [1.731747852E12, 16188.0], [1.731747817E12, 15760.0], [1.73174786E12, 15377.0], [1.731747815E12, 15711.0], [1.731747858E12, 15202.0], [1.731747823E12, 15733.0], [1.731747866E12, 16575.0], [1.731747819E12, 15957.0], [1.731747862E12, 15671.0], [1.731747821E12, 16462.0], [1.731747864E12, 15966.0], [1.731747827E12, 15726.0], [1.73174787E12, 16141.0], [1.731747829E12, 15664.0], [1.731747872E12, 15732.0], [1.731747825E12, 16114.0], [1.731747868E12, 16223.0], [1.731747833E12, 15721.0], [1.731747876E12, 14751.0], [1.731747831E12, 14987.0], [1.731747874E12, 15749.0], [1.731747839E12, 15939.0], [1.731747882E12, 15482.0], [1.731747835E12, 15602.0], [1.731747878E12, 15581.0], [1.731747837E12, 15927.0], [1.73174788E12, 15345.0]], "isOverall": false, "label": "Bytes sent per second", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731747889E12, "title": "Bytes Throughput Over Time"}},
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
        data: {"result": {"minY": 11.80952380952381, "minX": 1.731747799E12, "maxY": 14.837209302325583, "series": [{"data": [[1.731747843E12, 12.716417910447761], [1.731747886E12, 12.6231884057971], [1.731747845E12, 11.985294117647062], [1.731747888E12, 12.500000000000004], [1.731747802E12, 13.611940298507463], [1.731747841E12, 12.057142857142855], [1.731747884E12, 12.671641791044776], [1.7317478E12, 12.909090909090912], [1.731747849E12, 11.83076923076923], [1.731747806E12, 12.818181818181818], [1.731747808E12, 13.430769230769231], [1.731747804E12, 12.507462686567163], [1.731747847E12, 12.415384615384614], [1.731747812E12, 12.38235294117647], [1.731747855E12, 12.985294117647062], [1.731747851E12, 12.10769230769231], [1.731747853E12, 12.10769230769231], [1.73174781E12, 13.522388059701491], [1.731747859E12, 11.956521739130435], [1.731747861E12, 12.537313432835818], [1.731747818E12, 12.462686567164177], [1.731747857E12, 11.91304347826087], [1.731747814E12, 12.343283582089551], [1.731747816E12, 12.705882352941172], [1.731747865E12, 12.538461538461542], [1.731747822E12, 12.212121212121216], [1.731747824E12, 12.33846153846154], [1.73174782E12, 12.6], [1.731747863E12, 12.850746268656717], [1.731747828E12, 13.208955223880594], [1.731747871E12, 12.272727272727275], [1.731747867E12, 11.80952380952381], [1.731747869E12, 12.062499999999998], [1.731747826E12, 12.560606060606059], [1.731747875E12, 12.161764705882357], [1.731747877E12, 12.63235294117647], [1.731747834E12, 12.264705882352942], [1.731747873E12, 12.36764705882353], [1.73174783E12, 12.54411764705882], [1.731747832E12, 13.074626865671645], [1.731747881E12, 12.28985507246377], [1.731747838E12, 12.530303030303028], [1.73174784E12, 13.015384615384617], [1.731747836E12, 12.611940298507461], [1.731747879E12, 12.39130434782609], [1.731747801E12, 13.308823529411763], [1.731747844E12, 12.196969696969695], [1.731747887E12, 12.156250000000004], [1.731747883E12, 12.569230769230769], [1.731747885E12, 13.318181818181817], [1.731747799E12, 14.837209302325583], [1.731747842E12, 12.140625000000002], [1.731747807E12, 12.579710144927537], [1.73174785E12, 12.088235294117647], [1.731747889E12, 11.80952380952381], [1.731747803E12, 13.191176470588237], [1.731747846E12, 12.298507462686569], [1.731747805E12, 13.01515151515152], [1.731747848E12, 12.367647058823524], [1.731747811E12, 12.46268656716418], [1.731747854E12, 12.432835820895523], [1.731747813E12, 12.828124999999996], [1.731747856E12, 12.4], [1.731747809E12, 12.865671641791046], [1.731747852E12, 12.101449275362318], [1.731747817E12, 12.651515151515147], [1.73174786E12, 12.138461538461536], [1.731747815E12, 12.590909090909092], [1.731747858E12, 12.874999999999998], [1.731747823E12, 12.73134328358209], [1.731747866E12, 12.0], [1.731747819E12, 11.97058823529412], [1.731747862E12, 12.848484848484851], [1.731747821E12, 12.652173913043486], [1.731747864E12, 12.117647058823527], [1.731747827E12, 12.597014925373134], [1.73174787E12, 12.499999999999998], [1.731747829E12, 12.424242424242426], [1.731747872E12, 12.358208955223882], [1.731747825E12, 13.194029850746274], [1.731747868E12, 11.956521739130435], [1.731747833E12, 12.863636363636367], [1.731747876E12, 12.593750000000002], [1.731747831E12, 12.815384615384618], [1.731747874E12, 12.136363636363635], [1.731747839E12, 12.477611940298507], [1.731747882E12, 12.545454545454549], [1.731747835E12, 12.590909090909093], [1.731747878E12, 12.830769230769228], [1.731747837E12, 12.632352941176471], [1.73174788E12, 12.523076923076925]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731747889E12, "title": "Response Time Over Time"}},
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
        data: {"result": {"minY": 11.793650793650794, "minX": 1.731747799E12, "maxY": 14.744186046511626, "series": [{"data": [[1.731747843E12, 12.716417910447761], [1.731747886E12, 12.6231884057971], [1.731747845E12, 11.985294117647062], [1.731747888E12, 12.485294117647062], [1.731747802E12, 13.52238805970149], [1.731747841E12, 12.028571428571428], [1.731747884E12, 12.671641791044776], [1.7317478E12, 12.818181818181813], [1.731747849E12, 11.83076923076923], [1.731747806E12, 12.803030303030306], [1.731747808E12, 13.415384615384616], [1.731747804E12, 12.447761194029853], [1.731747847E12, 12.36923076923077], [1.731747812E12, 12.367647058823529], [1.731747855E12, 12.970588235294118], [1.731747851E12, 12.10769230769231], [1.731747853E12, 12.092307692307696], [1.73174781E12, 13.522388059701491], [1.731747859E12, 11.942028985507244], [1.731747861E12, 12.537313432835818], [1.731747818E12, 12.447761194029852], [1.731747857E12, 11.855072463768115], [1.731747814E12, 12.343283582089551], [1.731747816E12, 12.705882352941172], [1.731747865E12, 12.538461538461542], [1.731747822E12, 12.196969696969699], [1.731747824E12, 12.307692307692307], [1.73174782E12, 12.584615384615386], [1.731747863E12, 12.850746268656717], [1.731747828E12, 13.16417910447761], [1.731747871E12, 12.242424242424244], [1.731747867E12, 11.793650793650794], [1.731747869E12, 12.062499999999998], [1.731747826E12, 12.54545454545454], [1.731747875E12, 12.147058823529415], [1.731747877E12, 12.63235294117647], [1.731747834E12, 12.220588235294116], [1.731747873E12, 12.36764705882353], [1.73174783E12, 12.514705882352946], [1.731747832E12, 13.044776119402986], [1.731747881E12, 12.28985507246377], [1.731747838E12, 12.5], [1.73174784E12, 13.015384615384617], [1.731747836E12, 12.597014925373132], [1.731747879E12, 12.39130434782609], [1.731747801E12, 13.20588235294118], [1.731747844E12, 12.196969696969695], [1.731747887E12, 12.156250000000004], [1.731747883E12, 12.569230769230769], [1.731747885E12, 13.318181818181817], [1.731747799E12, 14.744186046511626], [1.731747842E12, 12.140625000000002], [1.731747807E12, 12.507246376811592], [1.73174785E12, 12.088235294117647], [1.731747889E12, 11.80952380952381], [1.731747803E12, 13.147058823529411], [1.731747846E12, 12.298507462686569], [1.731747805E12, 13.000000000000004], [1.731747848E12, 12.352941176470587], [1.731747811E12, 12.44776119402985], [1.731747854E12, 12.432835820895523], [1.731747813E12, 12.828124999999996], [1.731747856E12, 12.384615384615385], [1.731747809E12, 12.835820895522387], [1.731747852E12, 12.101449275362318], [1.731747817E12, 12.651515151515147], [1.73174786E12, 12.12307692307692], [1.731747815E12, 12.590909090909092], [1.731747858E12, 12.812499999999998], [1.731747823E12, 12.73134328358209], [1.731747866E12, 11.985714285714284], [1.731747819E12, 11.97058823529412], [1.731747862E12, 12.848484848484851], [1.731747821E12, 12.637681159420294], [1.731747864E12, 12.117647058823527], [1.731747827E12, 12.567164179104475], [1.73174787E12, 12.485294117647054], [1.731747829E12, 12.424242424242426], [1.731747872E12, 12.358208955223882], [1.731747825E12, 13.194029850746274], [1.731747868E12, 11.956521739130435], [1.731747833E12, 12.848484848484848], [1.731747876E12, 12.593750000000002], [1.731747831E12, 12.753846153846155], [1.731747874E12, 12.136363636363635], [1.731747839E12, 12.447761194029853], [1.731747882E12, 12.545454545454549], [1.731747835E12, 12.575757575757578], [1.731747878E12, 12.799999999999999], [1.731747837E12, 12.617647058823529], [1.73174788E12, 12.523076923076925]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731747889E12, "title": "Latencies Over Time"}},
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
        data: {"result": {"minY": 0.014925373134328358, "minX": 1.731747799E12, "maxY": 0.7674418604651163, "series": [{"data": [[1.731747843E12, 0.07462686567164181], [1.731747886E12, 0.08695652173913046], [1.731747845E12, 0.14705882352941183], [1.731747888E12, 0.058823529411764705], [1.731747802E12, 0.26865671641791056], [1.731747841E12, 0.15714285714285714], [1.731747884E12, 0.11940298507462688], [1.7317478E12, 0.19696969696969696], [1.731747849E12, 0.18461538461538465], [1.731747806E12, 0.10606060606060605], [1.731747808E12, 0.06153846153846153], [1.731747804E12, 0.1492537313432836], [1.731747847E12, 0.10769230769230774], [1.731747812E12, 0.1764705882352941], [1.731747855E12, 0.044117647058823546], [1.731747851E12, 0.10769230769230771], [1.731747853E12, 0.07692307692307694], [1.73174781E12, 0.05970149253731344], [1.731747859E12, 0.10144927536231887], [1.731747861E12, 0.05970149253731343], [1.731747818E12, 0.10447761194029855], [1.731747857E12, 0.13043478260869568], [1.731747814E12, 0.16417910447761203], [1.731747816E12, 0.1029411764705882], [1.731747865E12, 0.09230769230769233], [1.731747822E12, 0.18181818181818188], [1.731747824E12, 0.13846153846153844], [1.73174782E12, 0.10769230769230774], [1.731747863E12, 0.0746268656716418], [1.731747828E12, 0.07462686567164183], [1.731747871E12, 0.12121212121212123], [1.731747867E12, 0.09523809523809523], [1.731747869E12, 0.10937500000000003], [1.731747826E12, 0.1212121212121212], [1.731747875E12, 0.07352941176470588], [1.731747877E12, 0.10294117647058824], [1.731747834E12, 0.1470588235294118], [1.731747873E12, 0.11764705882352945], [1.73174783E12, 0.14705882352941185], [1.731747832E12, 0.08955223880597017], [1.731747881E12, 0.13043478260869568], [1.731747838E12, 0.10606060606060612], [1.73174784E12, 0.09230769230769233], [1.731747836E12, 0.14925373134328362], [1.731747879E12, 0.07246376811594203], [1.731747801E12, 0.13235294117647067], [1.731747844E12, 0.15151515151515157], [1.731747887E12, 0.15625000000000008], [1.731747883E12, 0.07692307692307693], [1.731747885E12, 0.060606060606060615], [1.731747799E12, 0.7674418604651163], [1.731747842E12, 0.14062500000000003], [1.731747807E12, 0.17391304347826095], [1.73174785E12, 0.10294117647058824], [1.731747889E12, 0.09523809523809523], [1.731747803E12, 0.10294117647058827], [1.731747846E12, 0.13432835820895533], [1.731747805E12, 0.06060606060606063], [1.731747848E12, 0.0735294117647059], [1.731747811E12, 0.14925373134328362], [1.731747854E12, 0.10447761194029852], [1.731747813E12, 0.09375000000000001], [1.731747856E12, 0.13846153846153852], [1.731747809E12, 0.13432835820895522], [1.731747852E12, 0.07246376811594206], [1.731747817E12, 0.07575757575757576], [1.73174786E12, 0.12307692307692308], [1.731747815E12, 0.16666666666666674], [1.731747858E12, 0.06250000000000001], [1.731747823E12, 0.10447761194029852], [1.731747866E12, 0.1142857142857143], [1.731747819E12, 0.161764705882353], [1.731747862E12, 0.04545454545454547], [1.731747821E12, 0.13043478260869573], [1.731747864E12, 0.0735294117647059], [1.731747827E12, 0.14925373134328362], [1.73174787E12, 0.058823529411764705], [1.731747829E12, 0.19696969696969707], [1.731747872E12, 0.11940298507462688], [1.731747825E12, 0.014925373134328358], [1.731747868E12, 0.10144927536231885], [1.731747833E12, 0.09090909090909091], [1.731747876E12, 0.10937500000000001], [1.731747831E12, 0.1230769230769231], [1.731747874E12, 0.13636363636363638], [1.731747839E12, 0.08955223880597019], [1.731747882E12, 0.09090909090909093], [1.731747835E12, 0.12121212121212123], [1.731747878E12, 0.12307692307692308], [1.731747837E12, 0.1323529411764706], [1.73174788E12, 0.09230769230769231]], "isOverall": false, "label": "Products", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731747889E12, "title": "Connect Time Over Time"}},
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
        data: {"result": {"minY": 12.0, "minX": 1.731747799E12, "maxY": 26.0, "series": [{"data": [[1.731747843E12, 16.0], [1.731747886E12, 15.0], [1.731747845E12, 15.0], [1.731747888E12, 15.0], [1.731747802E12, 26.0], [1.731747841E12, 15.0], [1.731747884E12, 16.0], [1.7317478E12, 16.0], [1.731747849E12, 15.0], [1.731747806E12, 16.0], [1.731747808E12, 17.0], [1.731747804E12, 18.0], [1.731747847E12, 15.0], [1.731747812E12, 15.0], [1.731747855E12, 15.0], [1.731747851E12, 16.0], [1.731747853E12, 15.0], [1.73174781E12, 16.0], [1.731747859E12, 16.0], [1.731747861E12, 17.0], [1.731747818E12, 15.0], [1.731747857E12, 15.0], [1.731747814E12, 17.0], [1.731747816E12, 15.0], [1.731747865E12, 15.0], [1.731747822E12, 15.0], [1.731747824E12, 15.0], [1.73174782E12, 16.0], [1.731747863E12, 15.0], [1.731747828E12, 15.0], [1.731747871E12, 15.0], [1.731747867E12, 15.0], [1.731747869E12, 15.0], [1.731747826E12, 22.0], [1.731747875E12, 17.0], [1.731747877E12, 15.0], [1.731747834E12, 15.0], [1.731747873E12, 15.0], [1.73174783E12, 16.0], [1.731747832E12, 15.0], [1.731747881E12, 17.0], [1.731747838E12, 15.0], [1.73174784E12, 16.0], [1.731747836E12, 16.0], [1.731747879E12, 16.0], [1.731747801E12, 16.0], [1.731747844E12, 15.0], [1.731747887E12, 15.0], [1.731747883E12, 15.0], [1.731747885E12, 17.0], [1.731747799E12, 21.0], [1.731747842E12, 15.0], [1.731747807E12, 16.0], [1.73174785E12, 16.0], [1.731747889E12, 14.0], [1.731747803E12, 16.0], [1.731747846E12, 15.0], [1.731747805E12, 16.0], [1.731747848E12, 16.0], [1.731747811E12, 15.0], [1.731747854E12, 15.0], [1.731747813E12, 18.0], [1.731747856E12, 17.0], [1.731747809E12, 16.0], [1.731747852E12, 14.0], [1.731747817E12, 16.0], [1.73174786E12, 16.0], [1.731747815E12, 15.0], [1.731747858E12, 16.0], [1.731747823E12, 15.0], [1.731747866E12, 15.0], [1.731747819E12, 15.0], [1.731747862E12, 15.0], [1.731747821E12, 15.0], [1.731747864E12, 15.0], [1.731747827E12, 15.0], [1.73174787E12, 15.0], [1.731747829E12, 15.0], [1.731747872E12, 17.0], [1.731747825E12, 16.0], [1.731747868E12, 14.0], [1.731747833E12, 15.0], [1.731747876E12, 16.0], [1.731747831E12, 15.0], [1.731747874E12, 15.0], [1.731747839E12, 15.0], [1.731747882E12, 16.0], [1.731747835E12, 15.0], [1.731747878E12, 15.0], [1.731747837E12, 16.0], [1.73174788E12, 14.0]], "isOverall": false, "label": "Max", "isController": false}, {"data": [[1.731747843E12, 14.0], [1.731747886E12, 14.0], [1.731747845E12, 14.0], [1.731747888E12, 14.0], [1.731747802E12, 14.0], [1.731747841E12, 14.0], [1.731747884E12, 14.0], [1.7317478E12, 14.300000000000004], [1.731747849E12, 14.0], [1.731747806E12, 14.0], [1.731747808E12, 15.0], [1.731747804E12, 15.0], [1.731747847E12, 14.0], [1.731747812E12, 14.0], [1.731747855E12, 14.0], [1.731747851E12, 14.0], [1.731747853E12, 13.100000000000001], [1.73174781E12, 14.0], [1.731747859E12, 13.0], [1.731747861E12, 14.0], [1.731747818E12, 14.0], [1.731747857E12, 14.0], [1.731747814E12, 14.399999999999999], [1.731747816E12, 14.0], [1.731747865E12, 15.0], [1.731747822E12, 14.0], [1.731747824E12, 14.0], [1.73174782E12, 14.0], [1.731747863E12, 14.700000000000003], [1.731747828E12, 14.0], [1.731747871E12, 14.0], [1.731747867E12, 14.0], [1.731747869E12, 14.0], [1.731747826E12, 14.0], [1.731747875E12, 14.0], [1.731747877E12, 14.0], [1.731747834E12, 14.0], [1.731747873E12, 13.0], [1.73174783E12, 15.0], [1.731747832E12, 14.0], [1.731747881E12, 14.0], [1.731747838E12, 14.0], [1.73174784E12, 14.0], [1.731747836E12, 14.0], [1.731747879E12, 14.0], [1.731747801E12, 15.0], [1.731747844E12, 14.0], [1.731747887E12, 14.0], [1.731747883E12, 14.0], [1.731747885E12, 14.0], [1.731747799E12, 17.1], [1.731747842E12, 14.0], [1.731747807E12, 14.200000000000003], [1.73174785E12, 14.0], [1.731747889E12, 14.0], [1.731747803E12, 15.0], [1.731747846E12, 13.0], [1.731747805E12, 14.0], [1.731747848E12, 13.0], [1.731747811E12, 14.200000000000003], [1.731747854E12, 14.0], [1.731747813E12, 14.0], [1.731747856E12, 14.200000000000003], [1.731747809E12, 14.0], [1.731747852E12, 13.0], [1.731747817E12, 13.700000000000003], [1.73174786E12, 14.0], [1.731747815E12, 15.0], [1.731747858E12, 14.0], [1.731747823E12, 14.0], [1.731747866E12, 13.0], [1.731747819E12, 14.0], [1.731747862E12, 14.0], [1.731747821E12, 14.0], [1.731747864E12, 14.0], [1.731747827E12, 14.0], [1.73174787E12, 13.300000000000004], [1.731747829E12, 15.0], [1.731747872E12, 14.0], [1.731747825E12, 14.0], [1.731747868E12, 13.700000000000003], [1.731747833E12, 14.800000000000004], [1.731747876E12, 14.0], [1.731747831E12, 14.0], [1.731747874E12, 14.0], [1.731747839E12, 14.0], [1.731747882E12, 15.0], [1.731747835E12, 14.0], [1.731747878E12, 14.0], [1.731747837E12, 14.100000000000001], [1.73174788E12, 14.0]], "isOverall": false, "label": "90th percentile", "isController": false}, {"data": [[1.731747843E12, 16.0], [1.731747886E12, 15.0], [1.731747845E12, 15.0], [1.731747888E12, 15.0], [1.731747802E12, 26.0], [1.731747841E12, 15.0], [1.731747884E12, 16.0], [1.7317478E12, 16.0], [1.731747849E12, 15.0], [1.731747806E12, 16.0], [1.731747808E12, 17.0], [1.731747804E12, 18.0], [1.731747847E12, 15.0], [1.731747812E12, 15.0], [1.731747855E12, 15.0], [1.731747851E12, 16.0], [1.731747853E12, 15.0], [1.73174781E12, 16.0], [1.731747859E12, 16.0], [1.731747861E12, 17.0], [1.731747818E12, 15.0], [1.731747857E12, 15.0], [1.731747814E12, 17.0], [1.731747816E12, 15.0], [1.731747865E12, 15.0], [1.731747822E12, 15.0], [1.731747824E12, 15.0], [1.73174782E12, 16.0], [1.731747863E12, 15.0], [1.731747828E12, 15.0], [1.731747871E12, 15.0], [1.731747867E12, 15.0], [1.731747869E12, 15.0], [1.731747826E12, 22.0], [1.731747875E12, 17.0], [1.731747877E12, 15.0], [1.731747834E12, 15.0], [1.731747873E12, 15.0], [1.73174783E12, 16.0], [1.731747832E12, 15.0], [1.731747881E12, 17.0], [1.731747838E12, 15.0], [1.73174784E12, 16.0], [1.731747836E12, 16.0], [1.731747879E12, 16.0], [1.731747801E12, 16.0], [1.731747844E12, 15.0], [1.731747887E12, 15.0], [1.731747883E12, 15.0], [1.731747885E12, 17.0], [1.731747799E12, 21.0], [1.731747842E12, 15.0], [1.731747807E12, 16.0], [1.73174785E12, 16.0], [1.731747889E12, 14.0], [1.731747803E12, 16.0], [1.731747846E12, 15.0], [1.731747805E12, 16.0], [1.731747848E12, 16.0], [1.731747811E12, 15.0], [1.731747854E12, 15.0], [1.731747813E12, 18.0], [1.731747856E12, 17.0], [1.731747809E12, 16.0], [1.731747852E12, 14.0], [1.731747817E12, 16.0], [1.73174786E12, 16.0], [1.731747815E12, 15.0], [1.731747858E12, 16.0], [1.731747823E12, 15.0], [1.731747866E12, 15.0], [1.731747819E12, 15.0], [1.731747862E12, 15.0], [1.731747821E12, 15.0], [1.731747864E12, 15.0], [1.731747827E12, 15.0], [1.73174787E12, 15.0], [1.731747829E12, 15.0], [1.731747872E12, 17.0], [1.731747825E12, 16.0], [1.731747868E12, 14.0], [1.731747833E12, 15.0], [1.731747876E12, 16.0], [1.731747831E12, 15.0], [1.731747874E12, 15.0], [1.731747839E12, 15.0], [1.731747882E12, 16.0], [1.731747835E12, 15.0], [1.731747878E12, 15.0], [1.731747837E12, 16.0], [1.73174788E12, 14.0]], "isOverall": false, "label": "99th percentile", "isController": false}, {"data": [[1.731747843E12, 15.0], [1.731747886E12, 15.0], [1.731747845E12, 14.0], [1.731747888E12, 14.799999999999997], [1.731747802E12, 17.0], [1.731747841E12, 14.0], [1.731747884E12, 15.0], [1.7317478E12, 16.0], [1.731747849E12, 14.199999999999996], [1.731747806E12, 15.0], [1.731747808E12, 16.0], [1.731747804E12, 15.25], [1.731747847E12, 14.0], [1.731747812E12, 15.0], [1.731747855E12, 14.649999999999999], [1.731747851E12, 15.0], [1.731747853E12, 14.0], [1.73174781E12, 15.0], [1.731747859E12, 14.0], [1.731747861E12, 14.0], [1.731747818E12, 15.0], [1.731747857E12, 15.0], [1.731747814E12, 15.0], [1.731747816E12, 15.0], [1.731747865E12, 15.0], [1.731747822E12, 15.0], [1.731747824E12, 15.0], [1.73174782E12, 15.0], [1.731747863E12, 15.0], [1.731747828E12, 15.0], [1.731747871E12, 14.0], [1.731747867E12, 14.0], [1.731747869E12, 15.0], [1.731747826E12, 15.0], [1.731747875E12, 14.0], [1.731747877E12, 14.75], [1.731747834E12, 15.0], [1.731747873E12, 14.799999999999997], [1.73174783E12, 15.049999999999997], [1.731747832E12, 15.0], [1.731747881E12, 15.0], [1.731747838E12, 14.949999999999996], [1.73174784E12, 15.0], [1.731747836E12, 15.0], [1.731747879E12, 15.0], [1.731747801E12, 15.0], [1.731747844E12, 15.0], [1.731747887E12, 15.0], [1.731747883E12, 15.0], [1.731747885E12, 15.0], [1.731747799E12, 19.099999999999994], [1.731747842E12, 14.199999999999996], [1.731747807E12, 15.0], [1.73174785E12, 14.0], [1.731747889E12, 14.0], [1.731747803E12, 15.0], [1.731747846E12, 14.899999999999999], [1.731747805E12, 14.899999999999999], [1.731747848E12, 14.0], [1.731747811E12, 15.0], [1.731747854E12, 14.0], [1.731747813E12, 15.0], [1.731747856E12, 15.0], [1.731747809E12, 15.0], [1.731747852E12, 14.0], [1.731747817E12, 15.0], [1.73174786E12, 15.0], [1.731747815E12, 15.0], [1.731747858E12, 15.0], [1.731747823E12, 14.799999999999997], [1.731747866E12, 14.849999999999994], [1.731747819E12, 15.0], [1.731747862E12, 14.0], [1.731747821E12, 14.899999999999999], [1.731747864E12, 14.0], [1.731747827E12, 15.0], [1.73174787E12, 14.649999999999999], [1.731747829E12, 15.0], [1.731747872E12, 15.0], [1.731747825E12, 15.0], [1.731747868E12, 14.0], [1.731747833E12, 15.0], [1.731747876E12, 14.049999999999997], [1.731747831E12, 15.0], [1.731747874E12, 15.0], [1.731747839E12, 14.949999999999996], [1.731747882E12, 15.049999999999997], [1.731747835E12, 15.0], [1.731747878E12, 15.0], [1.731747837E12, 15.0], [1.73174788E12, 14.0]], "isOverall": false, "label": "95th percentile", "isController": false}, {"data": [[1.731747843E12, 12.0], [1.731747886E12, 12.0], [1.731747845E12, 12.0], [1.731747888E12, 12.0], [1.731747802E12, 13.0], [1.731747841E12, 12.0], [1.731747884E12, 12.0], [1.7317478E12, 13.0], [1.731747849E12, 12.0], [1.731747806E12, 13.0], [1.731747808E12, 13.0], [1.731747804E12, 13.0], [1.731747847E12, 12.0], [1.731747812E12, 12.0], [1.731747855E12, 12.0], [1.731747851E12, 12.0], [1.731747853E12, 12.0], [1.73174781E12, 13.0], [1.731747859E12, 12.0], [1.731747861E12, 12.0], [1.731747818E12, 12.0], [1.731747857E12, 12.0], [1.731747814E12, 12.0], [1.731747816E12, 12.0], [1.731747865E12, 12.0], [1.731747822E12, 12.0], [1.731747824E12, 12.0], [1.73174782E12, 12.0], [1.731747863E12, 12.0], [1.731747828E12, 13.0], [1.731747871E12, 12.0], [1.731747867E12, 12.0], [1.731747869E12, 12.0], [1.731747826E12, 12.0], [1.731747875E12, 12.0], [1.731747877E12, 12.0], [1.731747834E12, 12.0], [1.731747873E12, 12.0], [1.73174783E12, 13.0], [1.731747832E12, 13.0], [1.731747881E12, 12.0], [1.731747838E12, 12.0], [1.73174784E12, 12.0], [1.731747836E12, 12.0], [1.731747879E12, 12.0], [1.731747801E12, 13.0], [1.731747844E12, 12.0], [1.731747887E12, 12.0], [1.731747883E12, 12.0], [1.731747885E12, 13.0], [1.731747799E12, 13.0], [1.731747842E12, 12.0], [1.731747807E12, 12.0], [1.73174785E12, 12.0], [1.731747889E12, 12.0], [1.731747803E12, 13.0], [1.731747846E12, 12.0], [1.731747805E12, 12.0], [1.731747848E12, 12.0], [1.731747811E12, 12.0], [1.731747854E12, 12.0], [1.731747813E12, 12.0], [1.731747856E12, 12.0], [1.731747809E12, 13.0], [1.731747852E12, 12.0], [1.731747817E12, 12.0], [1.73174786E12, 12.0], [1.731747815E12, 12.0], [1.731747858E12, 12.0], [1.731747823E12, 12.0], [1.731747866E12, 12.0], [1.731747819E12, 12.0], [1.731747862E12, 12.0], [1.731747821E12, 12.0], [1.731747864E12, 12.0], [1.731747827E12, 13.0], [1.73174787E12, 12.0], [1.731747829E12, 13.0], [1.731747872E12, 12.0], [1.731747825E12, 12.0], [1.731747868E12, 12.0], [1.731747833E12, 12.0], [1.731747876E12, 12.0], [1.731747831E12, 13.0], [1.731747874E12, 12.0], [1.731747839E12, 12.0], [1.731747882E12, 12.0], [1.731747835E12, 12.0], [1.731747878E12, 12.0], [1.731747837E12, 12.0], [1.73174788E12, 13.0]], "isOverall": false, "label": "Min", "isController": false}, {"data": [[1.731747843E12, 13.0], [1.731747886E12, 13.0], [1.731747845E12, 13.0], [1.731747888E12, 13.0], [1.731747802E12, 14.0], [1.731747841E12, 13.0], [1.731747884E12, 13.0], [1.7317478E12, 14.0], [1.731747849E12, 13.0], [1.731747806E12, 13.0], [1.731747808E12, 13.0], [1.731747804E12, 13.0], [1.731747847E12, 13.0], [1.731747812E12, 13.0], [1.731747855E12, 13.0], [1.731747851E12, 13.0], [1.731747853E12, 13.0], [1.73174781E12, 14.0], [1.731747859E12, 13.0], [1.731747861E12, 13.0], [1.731747818E12, 13.0], [1.731747857E12, 13.0], [1.731747814E12, 13.0], [1.731747816E12, 13.0], [1.731747865E12, 13.0], [1.731747822E12, 13.0], [1.731747824E12, 13.0], [1.73174782E12, 13.0], [1.731747863E12, 13.0], [1.731747828E12, 13.0], [1.731747871E12, 13.0], [1.731747867E12, 12.0], [1.731747869E12, 13.0], [1.731747826E12, 13.0], [1.731747875E12, 13.0], [1.731747877E12, 13.0], [1.731747834E12, 13.0], [1.731747873E12, 13.0], [1.73174783E12, 13.0], [1.731747832E12, 13.0], [1.731747881E12, 13.0], [1.731747838E12, 13.0], [1.73174784E12, 13.0], [1.731747836E12, 13.0], [1.731747879E12, 13.0], [1.731747801E12, 14.0], [1.731747844E12, 13.0], [1.731747887E12, 13.0], [1.731747883E12, 13.0], [1.731747885E12, 13.0], [1.731747799E12, 14.0], [1.731747842E12, 13.0], [1.731747807E12, 13.0], [1.73174785E12, 13.0], [1.731747889E12, 13.0], [1.731747803E12, 13.0], [1.731747846E12, 13.0], [1.731747805E12, 13.0], [1.731747848E12, 13.0], [1.731747811E12, 13.0], [1.731747854E12, 13.0], [1.731747813E12, 13.0], [1.731747856E12, 13.0], [1.731747809E12, 13.0], [1.731747852E12, 13.0], [1.731747817E12, 13.0], [1.73174786E12, 13.0], [1.731747815E12, 13.0], [1.731747858E12, 13.0], [1.731747823E12, 13.0], [1.731747866E12, 13.0], [1.731747819E12, 13.0], [1.731747862E12, 13.0], [1.731747821E12, 13.0], [1.731747864E12, 13.0], [1.731747827E12, 13.0], [1.73174787E12, 13.0], [1.731747829E12, 13.0], [1.731747872E12, 13.0], [1.731747825E12, 13.0], [1.731747868E12, 12.0], [1.731747833E12, 13.0], [1.731747876E12, 13.0], [1.731747831E12, 13.0], [1.731747874E12, 13.0], [1.731747839E12, 13.0], [1.731747882E12, 13.0], [1.731747835E12, 13.0], [1.731747878E12, 13.0], [1.731747837E12, 13.0], [1.73174788E12, 13.0]], "isOverall": false, "label": "Median", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731747889E12, "title": "Response Time Percentiles Over Time (successful requests only)"}},
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
    data: {"result": {"minY": 6.5, "minX": 21.0, "maxY": 14.0, "series": [{"data": [[66.0, 13.0], [67.0, 13.0], [65.0, 13.0], [64.0, 13.0], [68.0, 13.0], [69.0, 13.0], [70.0, 13.0], [43.0, 14.0], [21.0, 13.0], [63.0, 12.0]], "isOverall": false, "label": "Successes", "isController": false}, {"data": [[66.0, 7.0], [67.0, 7.0], [65.0, 7.0], [64.0, 7.0], [68.0, 7.0], [69.0, 7.0], [70.0, 7.0], [43.0, 13.0], [21.0, 6.5], [63.0, 7.0]], "isOverall": false, "label": "Failures", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 70.0, "title": "Response Time Vs Request"}},
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
    data: {"result": {"minY": 6.5, "minX": 21.0, "maxY": 14.0, "series": [{"data": [[66.0, 13.0], [67.0, 13.0], [65.0, 13.0], [64.0, 13.0], [68.0, 13.0], [69.0, 13.0], [70.0, 13.0], [43.0, 14.0], [21.0, 13.0], [63.0, 12.0]], "isOverall": false, "label": "Successes", "isController": false}, {"data": [[66.0, 7.0], [67.0, 7.0], [65.0, 7.0], [64.0, 7.0], [68.0, 7.0], [69.0, 7.0], [70.0, 7.0], [43.0, 13.0], [21.0, 6.5], [63.0, 7.0]], "isOverall": false, "label": "Failures", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 70.0, "title": "Latencies Vs Request"}},
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
        data: {"result": {"minY": 20.0, "minX": 1.731747799E12, "maxY": 70.0, "series": [{"data": [[1.731747843E12, 67.0], [1.731747886E12, 69.0], [1.731747845E12, 68.0], [1.731747888E12, 68.0], [1.731747802E12, 67.0], [1.731747841E12, 70.0], [1.731747884E12, 67.0], [1.7317478E12, 66.0], [1.731747849E12, 65.0], [1.731747806E12, 66.0], [1.731747808E12, 64.0], [1.731747804E12, 67.0], [1.731747847E12, 66.0], [1.731747812E12, 67.0], [1.731747855E12, 67.0], [1.731747851E12, 65.0], [1.731747853E12, 64.0], [1.73174781E12, 67.0], [1.731747859E12, 69.0], [1.731747861E12, 67.0], [1.731747818E12, 68.0], [1.731747857E12, 69.0], [1.731747814E12, 67.0], [1.731747816E12, 68.0], [1.731747865E12, 66.0], [1.731747822E12, 66.0], [1.731747824E12, 65.0], [1.73174782E12, 66.0], [1.731747863E12, 67.0], [1.731747828E12, 67.0], [1.731747871E12, 65.0], [1.731747867E12, 64.0], [1.731747869E12, 64.0], [1.731747826E12, 66.0], [1.731747875E12, 68.0], [1.731747877E12, 68.0], [1.731747834E12, 68.0], [1.731747873E12, 67.0], [1.73174783E12, 68.0], [1.731747832E12, 67.0], [1.731747881E12, 69.0], [1.731747838E12, 67.0], [1.73174784E12, 65.0], [1.731747836E12, 68.0], [1.731747879E12, 69.0], [1.731747801E12, 68.0], [1.731747844E12, 66.0], [1.731747887E12, 64.0], [1.731747883E12, 66.0], [1.731747885E12, 66.0], [1.731747799E12, 44.0], [1.731747842E12, 64.0], [1.731747807E12, 69.0], [1.73174785E12, 68.0], [1.731747889E12, 20.0], [1.731747803E12, 68.0], [1.731747846E12, 66.0], [1.731747805E12, 66.0], [1.731747848E12, 68.0], [1.731747811E12, 67.0], [1.731747854E12, 68.0], [1.731747813E12, 65.0], [1.731747856E12, 66.0], [1.731747809E12, 68.0], [1.731747852E12, 69.0], [1.731747817E12, 65.0], [1.73174786E12, 65.0], [1.731747815E12, 66.0], [1.731747858E12, 64.0], [1.731747823E12, 67.0], [1.731747866E12, 69.0], [1.731747819E12, 67.0], [1.731747862E12, 66.0], [1.731747821E12, 69.0], [1.731747864E12, 67.0], [1.731747827E12, 67.0], [1.73174787E12, 68.0], [1.731747829E12, 66.0], [1.731747872E12, 68.0], [1.731747825E12, 67.0], [1.731747868E12, 69.0], [1.731747833E12, 66.0], [1.731747876E12, 64.0], [1.731747831E12, 65.0], [1.731747874E12, 67.0], [1.731747839E12, 67.0], [1.731747882E12, 65.0], [1.731747835E12, 65.0], [1.731747878E12, 65.0], [1.731747837E12, 67.0], [1.73174788E12, 65.0]], "isOverall": false, "label": "hitsPerSecond", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731747889E12, "title": "Hits Per Second"}},
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
        data: {"result": {"minY": 1.0, "minX": 1.731747799E12, "maxY": 67.0, "series": [{"data": [[1.731747843E12, 64.0], [1.731747886E12, 62.0], [1.731747845E12, 58.0], [1.731747888E12, 63.0], [1.731747802E12, 63.0], [1.731747841E12, 59.0], [1.731747884E12, 59.0], [1.7317478E12, 56.0], [1.731747849E12, 55.0], [1.731747806E12, 58.0], [1.731747808E12, 61.0], [1.731747804E12, 54.0], [1.731747847E12, 61.0], [1.731747812E12, 59.0], [1.731747855E12, 66.0], [1.731747851E12, 57.0], [1.731747853E12, 58.0], [1.73174781E12, 66.0], [1.731747859E12, 57.0], [1.731747861E12, 61.0], [1.731747818E12, 62.0], [1.731747857E12, 57.0], [1.731747814E12, 55.0], [1.731747816E12, 62.0], [1.731747865E12, 57.0], [1.731747822E12, 54.0], [1.731747824E12, 57.0], [1.73174782E12, 59.0], [1.731747863E12, 62.0], [1.731747828E12, 64.0], [1.731747871E12, 59.0], [1.731747867E12, 55.0], [1.731747869E12, 57.0], [1.731747826E12, 56.0], [1.731747875E12, 58.0], [1.731747877E12, 64.0], [1.731747834E12, 58.0], [1.731747873E12, 63.0], [1.73174783E12, 58.0], [1.731747832E12, 63.0], [1.731747881E12, 61.0], [1.731747838E12, 60.0], [1.73174784E12, 64.0], [1.731747836E12, 59.0], [1.731747879E12, 59.0], [1.731747801E12, 62.0], [1.731747844E12, 54.0], [1.731747887E12, 53.0], [1.731747883E12, 59.0], [1.731747885E12, 64.0], [1.731747799E12, 38.0], [1.731747842E12, 55.0], [1.731747807E12, 57.0], [1.73174785E12, 60.0], [1.731747889E12, 17.0], [1.731747803E12, 63.0], [1.731747846E12, 61.0], [1.731747805E12, 61.0], [1.731747848E12, 63.0], [1.731747811E12, 57.0], [1.731747854E12, 60.0], [1.731747813E12, 61.0], [1.731747856E12, 57.0], [1.731747809E12, 59.0], [1.731747852E12, 61.0], [1.731747817E12, 62.0], [1.73174786E12, 55.0], [1.731747815E12, 56.0], [1.731747858E12, 61.0], [1.731747823E12, 63.0], [1.731747866E12, 62.0], [1.731747819E12, 56.0], [1.731747862E12, 62.0], [1.731747821E12, 61.0], [1.731747864E12, 58.0], [1.731747827E12, 57.0], [1.73174787E12, 66.0], [1.731747829E12, 54.0], [1.731747872E12, 56.0], [1.731747825E12, 67.0], [1.731747868E12, 62.0], [1.731747833E12, 61.0], [1.731747876E12, 58.0], [1.731747831E12, 59.0], [1.731747874E12, 54.0], [1.731747839E12, 60.0], [1.731747882E12, 58.0], [1.731747835E12, 58.0], [1.731747878E12, 60.0], [1.731747837E12, 58.0], [1.73174788E12, 57.0]], "isOverall": false, "label": "200", "isController": false}, {"data": [[1.731747843E12, 3.0], [1.731747886E12, 7.0], [1.731747845E12, 10.0], [1.731747888E12, 5.0], [1.731747802E12, 4.0], [1.731747841E12, 11.0], [1.731747884E12, 8.0], [1.7317478E12, 10.0], [1.731747849E12, 10.0], [1.731747806E12, 8.0], [1.731747808E12, 4.0], [1.731747804E12, 13.0], [1.731747847E12, 4.0], [1.731747812E12, 9.0], [1.731747855E12, 2.0], [1.731747851E12, 8.0], [1.731747853E12, 7.0], [1.73174781E12, 1.0], [1.731747859E12, 12.0], [1.731747861E12, 6.0], [1.731747818E12, 5.0], [1.731747857E12, 12.0], [1.731747814E12, 12.0], [1.731747816E12, 6.0], [1.731747865E12, 8.0], [1.731747822E12, 12.0], [1.731747824E12, 8.0], [1.73174782E12, 6.0], [1.731747863E12, 5.0], [1.731747828E12, 3.0], [1.731747871E12, 7.0], [1.731747867E12, 8.0], [1.731747869E12, 7.0], [1.731747826E12, 10.0], [1.731747875E12, 10.0], [1.731747877E12, 4.0], [1.731747834E12, 10.0], [1.731747873E12, 5.0], [1.73174783E12, 10.0], [1.731747832E12, 4.0], [1.731747881E12, 8.0], [1.731747838E12, 6.0], [1.73174784E12, 1.0], [1.731747836E12, 8.0], [1.731747879E12, 10.0], [1.731747801E12, 6.0], [1.731747844E12, 12.0], [1.731747887E12, 11.0], [1.731747883E12, 6.0], [1.731747885E12, 2.0], [1.731747799E12, 5.0], [1.731747842E12, 9.0], [1.731747807E12, 12.0], [1.73174785E12, 8.0], [1.731747889E12, 4.0], [1.731747803E12, 5.0], [1.731747846E12, 6.0], [1.731747805E12, 5.0], [1.731747848E12, 5.0], [1.731747811E12, 10.0], [1.731747854E12, 7.0], [1.731747813E12, 3.0], [1.731747856E12, 8.0], [1.731747809E12, 8.0], [1.731747852E12, 8.0], [1.731747817E12, 4.0], [1.73174786E12, 10.0], [1.731747815E12, 10.0], [1.731747858E12, 3.0], [1.731747823E12, 4.0], [1.731747866E12, 8.0], [1.731747819E12, 12.0], [1.731747862E12, 4.0], [1.731747821E12, 8.0], [1.731747864E12, 10.0], [1.731747827E12, 10.0], [1.73174787E12, 2.0], [1.731747829E12, 12.0], [1.731747872E12, 11.0], [1.731747868E12, 7.0], [1.731747833E12, 5.0], [1.731747876E12, 6.0], [1.731747831E12, 6.0], [1.731747874E12, 12.0], [1.731747839E12, 7.0], [1.731747882E12, 8.0], [1.731747835E12, 8.0], [1.731747878E12, 5.0], [1.731747837E12, 10.0], [1.73174788E12, 8.0]], "isOverall": false, "label": "500", "isController": false}], "supportsControllersDiscrimination": false, "granularity": 1000, "maxX": 1.731747889E12, "title": "Codes Per Second"}},
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
        data: {"result": {"minY": 1.0, "minX": 1.731747799E12, "maxY": 67.0, "series": [{"data": [[1.731747843E12, 3.0], [1.731747886E12, 7.0], [1.731747845E12, 10.0], [1.731747888E12, 5.0], [1.731747802E12, 4.0], [1.731747841E12, 11.0], [1.731747884E12, 8.0], [1.7317478E12, 10.0], [1.731747849E12, 10.0], [1.731747806E12, 8.0], [1.731747808E12, 4.0], [1.731747804E12, 13.0], [1.731747847E12, 4.0], [1.731747812E12, 9.0], [1.731747855E12, 2.0], [1.731747851E12, 8.0], [1.731747853E12, 7.0], [1.73174781E12, 1.0], [1.731747859E12, 12.0], [1.731747861E12, 6.0], [1.731747818E12, 5.0], [1.731747857E12, 12.0], [1.731747814E12, 12.0], [1.731747816E12, 6.0], [1.731747865E12, 8.0], [1.731747822E12, 12.0], [1.731747824E12, 8.0], [1.73174782E12, 6.0], [1.731747863E12, 5.0], [1.731747828E12, 3.0], [1.731747871E12, 7.0], [1.731747867E12, 8.0], [1.731747869E12, 7.0], [1.731747826E12, 10.0], [1.731747875E12, 10.0], [1.731747877E12, 4.0], [1.731747834E12, 10.0], [1.731747873E12, 5.0], [1.73174783E12, 10.0], [1.731747832E12, 4.0], [1.731747881E12, 8.0], [1.731747838E12, 6.0], [1.73174784E12, 1.0], [1.731747836E12, 8.0], [1.731747879E12, 10.0], [1.731747801E12, 6.0], [1.731747844E12, 12.0], [1.731747887E12, 11.0], [1.731747883E12, 6.0], [1.731747885E12, 2.0], [1.731747799E12, 5.0], [1.731747842E12, 9.0], [1.731747807E12, 12.0], [1.73174785E12, 8.0], [1.731747889E12, 4.0], [1.731747803E12, 5.0], [1.731747846E12, 6.0], [1.731747805E12, 5.0], [1.731747848E12, 5.0], [1.731747811E12, 10.0], [1.731747854E12, 7.0], [1.731747813E12, 3.0], [1.731747856E12, 8.0], [1.731747809E12, 8.0], [1.731747852E12, 8.0], [1.731747817E12, 4.0], [1.73174786E12, 10.0], [1.731747815E12, 10.0], [1.731747858E12, 3.0], [1.731747823E12, 4.0], [1.731747866E12, 8.0], [1.731747819E12, 12.0], [1.731747862E12, 4.0], [1.731747821E12, 8.0], [1.731747864E12, 10.0], [1.731747827E12, 10.0], [1.73174787E12, 2.0], [1.731747829E12, 12.0], [1.731747872E12, 11.0], [1.731747868E12, 7.0], [1.731747833E12, 5.0], [1.731747876E12, 6.0], [1.731747831E12, 6.0], [1.731747874E12, 12.0], [1.731747839E12, 7.0], [1.731747882E12, 8.0], [1.731747835E12, 8.0], [1.731747878E12, 5.0], [1.731747837E12, 10.0], [1.73174788E12, 8.0]], "isOverall": false, "label": "Products-failure", "isController": false}, {"data": [[1.731747843E12, 64.0], [1.731747886E12, 62.0], [1.731747845E12, 58.0], [1.731747888E12, 63.0], [1.731747802E12, 63.0], [1.731747841E12, 59.0], [1.731747884E12, 59.0], [1.7317478E12, 56.0], [1.731747849E12, 55.0], [1.731747806E12, 58.0], [1.731747808E12, 61.0], [1.731747804E12, 54.0], [1.731747847E12, 61.0], [1.731747812E12, 59.0], [1.731747855E12, 66.0], [1.731747851E12, 57.0], [1.731747853E12, 58.0], [1.73174781E12, 66.0], [1.731747859E12, 57.0], [1.731747861E12, 61.0], [1.731747818E12, 62.0], [1.731747857E12, 57.0], [1.731747814E12, 55.0], [1.731747816E12, 62.0], [1.731747865E12, 57.0], [1.731747822E12, 54.0], [1.731747824E12, 57.0], [1.73174782E12, 59.0], [1.731747863E12, 62.0], [1.731747828E12, 64.0], [1.731747871E12, 59.0], [1.731747867E12, 55.0], [1.731747869E12, 57.0], [1.731747826E12, 56.0], [1.731747875E12, 58.0], [1.731747877E12, 64.0], [1.731747834E12, 58.0], [1.731747873E12, 63.0], [1.73174783E12, 58.0], [1.731747832E12, 63.0], [1.731747881E12, 61.0], [1.731747838E12, 60.0], [1.73174784E12, 64.0], [1.731747836E12, 59.0], [1.731747879E12, 59.0], [1.731747801E12, 62.0], [1.731747844E12, 54.0], [1.731747887E12, 53.0], [1.731747883E12, 59.0], [1.731747885E12, 64.0], [1.731747799E12, 38.0], [1.731747842E12, 55.0], [1.731747807E12, 57.0], [1.73174785E12, 60.0], [1.731747889E12, 17.0], [1.731747803E12, 63.0], [1.731747846E12, 61.0], [1.731747805E12, 61.0], [1.731747848E12, 63.0], [1.731747811E12, 57.0], [1.731747854E12, 60.0], [1.731747813E12, 61.0], [1.731747856E12, 57.0], [1.731747809E12, 59.0], [1.731747852E12, 61.0], [1.731747817E12, 62.0], [1.73174786E12, 55.0], [1.731747815E12, 56.0], [1.731747858E12, 61.0], [1.731747823E12, 63.0], [1.731747866E12, 62.0], [1.731747819E12, 56.0], [1.731747862E12, 62.0], [1.731747821E12, 61.0], [1.731747864E12, 58.0], [1.731747827E12, 57.0], [1.73174787E12, 66.0], [1.731747829E12, 54.0], [1.731747872E12, 56.0], [1.731747825E12, 67.0], [1.731747868E12, 62.0], [1.731747833E12, 61.0], [1.731747876E12, 58.0], [1.731747831E12, 59.0], [1.731747874E12, 54.0], [1.731747839E12, 60.0], [1.731747882E12, 58.0], [1.731747835E12, 58.0], [1.731747878E12, 60.0], [1.731747837E12, 58.0], [1.73174788E12, 57.0]], "isOverall": false, "label": "Products-success", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731747889E12, "title": "Transactions Per Second"}},
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
        data: {"result": {"minY": 1.0, "minX": 1.731747799E12, "maxY": 67.0, "series": [{"data": [[1.731747843E12, 64.0], [1.731747886E12, 62.0], [1.731747845E12, 58.0], [1.731747888E12, 63.0], [1.731747802E12, 63.0], [1.731747841E12, 59.0], [1.731747884E12, 59.0], [1.7317478E12, 56.0], [1.731747849E12, 55.0], [1.731747806E12, 58.0], [1.731747808E12, 61.0], [1.731747804E12, 54.0], [1.731747847E12, 61.0], [1.731747812E12, 59.0], [1.731747855E12, 66.0], [1.731747851E12, 57.0], [1.731747853E12, 58.0], [1.73174781E12, 66.0], [1.731747859E12, 57.0], [1.731747861E12, 61.0], [1.731747818E12, 62.0], [1.731747857E12, 57.0], [1.731747814E12, 55.0], [1.731747816E12, 62.0], [1.731747865E12, 57.0], [1.731747822E12, 54.0], [1.731747824E12, 57.0], [1.73174782E12, 59.0], [1.731747863E12, 62.0], [1.731747828E12, 64.0], [1.731747871E12, 59.0], [1.731747867E12, 55.0], [1.731747869E12, 57.0], [1.731747826E12, 56.0], [1.731747875E12, 58.0], [1.731747877E12, 64.0], [1.731747834E12, 58.0], [1.731747873E12, 63.0], [1.73174783E12, 58.0], [1.731747832E12, 63.0], [1.731747881E12, 61.0], [1.731747838E12, 60.0], [1.73174784E12, 64.0], [1.731747836E12, 59.0], [1.731747879E12, 59.0], [1.731747801E12, 62.0], [1.731747844E12, 54.0], [1.731747887E12, 53.0], [1.731747883E12, 59.0], [1.731747885E12, 64.0], [1.731747799E12, 38.0], [1.731747842E12, 55.0], [1.731747807E12, 57.0], [1.73174785E12, 60.0], [1.731747889E12, 17.0], [1.731747803E12, 63.0], [1.731747846E12, 61.0], [1.731747805E12, 61.0], [1.731747848E12, 63.0], [1.731747811E12, 57.0], [1.731747854E12, 60.0], [1.731747813E12, 61.0], [1.731747856E12, 57.0], [1.731747809E12, 59.0], [1.731747852E12, 61.0], [1.731747817E12, 62.0], [1.73174786E12, 55.0], [1.731747815E12, 56.0], [1.731747858E12, 61.0], [1.731747823E12, 63.0], [1.731747866E12, 62.0], [1.731747819E12, 56.0], [1.731747862E12, 62.0], [1.731747821E12, 61.0], [1.731747864E12, 58.0], [1.731747827E12, 57.0], [1.73174787E12, 66.0], [1.731747829E12, 54.0], [1.731747872E12, 56.0], [1.731747825E12, 67.0], [1.731747868E12, 62.0], [1.731747833E12, 61.0], [1.731747876E12, 58.0], [1.731747831E12, 59.0], [1.731747874E12, 54.0], [1.731747839E12, 60.0], [1.731747882E12, 58.0], [1.731747835E12, 58.0], [1.731747878E12, 60.0], [1.731747837E12, 58.0], [1.73174788E12, 57.0]], "isOverall": false, "label": "Transaction-success", "isController": false}, {"data": [[1.731747843E12, 3.0], [1.731747886E12, 7.0], [1.731747845E12, 10.0], [1.731747888E12, 5.0], [1.731747802E12, 4.0], [1.731747841E12, 11.0], [1.731747884E12, 8.0], [1.7317478E12, 10.0], [1.731747849E12, 10.0], [1.731747806E12, 8.0], [1.731747808E12, 4.0], [1.731747804E12, 13.0], [1.731747847E12, 4.0], [1.731747812E12, 9.0], [1.731747855E12, 2.0], [1.731747851E12, 8.0], [1.731747853E12, 7.0], [1.73174781E12, 1.0], [1.731747859E12, 12.0], [1.731747861E12, 6.0], [1.731747818E12, 5.0], [1.731747857E12, 12.0], [1.731747814E12, 12.0], [1.731747816E12, 6.0], [1.731747865E12, 8.0], [1.731747822E12, 12.0], [1.731747824E12, 8.0], [1.73174782E12, 6.0], [1.731747863E12, 5.0], [1.731747828E12, 3.0], [1.731747871E12, 7.0], [1.731747867E12, 8.0], [1.731747869E12, 7.0], [1.731747826E12, 10.0], [1.731747875E12, 10.0], [1.731747877E12, 4.0], [1.731747834E12, 10.0], [1.731747873E12, 5.0], [1.73174783E12, 10.0], [1.731747832E12, 4.0], [1.731747881E12, 8.0], [1.731747838E12, 6.0], [1.73174784E12, 1.0], [1.731747836E12, 8.0], [1.731747879E12, 10.0], [1.731747801E12, 6.0], [1.731747844E12, 12.0], [1.731747887E12, 11.0], [1.731747883E12, 6.0], [1.731747885E12, 2.0], [1.731747799E12, 5.0], [1.731747842E12, 9.0], [1.731747807E12, 12.0], [1.73174785E12, 8.0], [1.731747889E12, 4.0], [1.731747803E12, 5.0], [1.731747846E12, 6.0], [1.731747805E12, 5.0], [1.731747848E12, 5.0], [1.731747811E12, 10.0], [1.731747854E12, 7.0], [1.731747813E12, 3.0], [1.731747856E12, 8.0], [1.731747809E12, 8.0], [1.731747852E12, 8.0], [1.731747817E12, 4.0], [1.73174786E12, 10.0], [1.731747815E12, 10.0], [1.731747858E12, 3.0], [1.731747823E12, 4.0], [1.731747866E12, 8.0], [1.731747819E12, 12.0], [1.731747862E12, 4.0], [1.731747821E12, 8.0], [1.731747864E12, 10.0], [1.731747827E12, 10.0], [1.73174787E12, 2.0], [1.731747829E12, 12.0], [1.731747872E12, 11.0], [1.731747868E12, 7.0], [1.731747833E12, 5.0], [1.731747876E12, 6.0], [1.731747831E12, 6.0], [1.731747874E12, 12.0], [1.731747839E12, 7.0], [1.731747882E12, 8.0], [1.731747835E12, 8.0], [1.731747878E12, 5.0], [1.731747837E12, 10.0], [1.73174788E12, 8.0]], "isOverall": false, "label": "Transaction-failure", "isController": false}], "supportsControllersDiscrimination": true, "granularity": 1000, "maxX": 1.731747889E12, "title": "Total Transactions Per Second"}},
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

