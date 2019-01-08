<?php

/**
 * @file
 * Default theme implementation to display SVG content with controls to be used
 * in an iFrame.
 *
 * Available variables:
 * - $id: the Diagram entity ID.
 *
 * @see template_preprocess()
 * @see template_preprocess_svg()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<!DOCTYPE html>
<html>
<head>
	<title>Result Chain</title>
	
 
<!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries --> 
<!-- WARNING: Respond.js doesn't work if you view the page via file:// --> 
<!--[if lt IE 9]> 
  <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script> 
  <script src="https://oss.maxcdn.com/libs/respond.js/1.3.0/respond.min.js"></script> 
<![endif]--> 

<link href="<?php print $modulePath; ?>front/css/bootstrap-dialog.min.css" rel="stylesheet"> 
<link rel="stylesheet" href="<?php print $modulePath; ?>front/css/main.css"> 
<link rel="stylesheet" href="<?php print $modulePath; ?>front/css/slider.css"> 
<link rel="stylesheet" href="<?php print $modulePath; ?>front/css/bootstrap-dialog.min.css"> 

<style> 
	
	.svg_select rect {
        stroke: #aaa;
        fill:   #ddd;
	}
	
	.svg_select text {
        stroke: #aaa;
        fill:   #888;
	}
	
	.svg_link rect {
        stroke: #333;
        fill:   #ffcc00;
	}
	
	.stile_testo_titolo {
		font-weight: bold ; 
	}
	
	.stile_testo_titolo_vertical {
		font-weight: bold ; 
		text-align: center ; 
	}
	
	/*
	.line {}
	
	.actionName {
		font-size : 12pt ; 
	}
	*/
	
	body{
		padding: 0px ; margin : 0px ; 
	}
</style>
</head>
<body>

<script src="<?php print $modulePath; ?>front/js/jquery.js"></script>

<script type="text/javascript">
  var basePath = '<?php print $basePath; ?>';
  var modulePath = '<?php print $modulePath; ?>';
$( document ).ready(function() {
	// alert('start');
	$('#t1').show();
	$('#t2').hide();
});

var testo_ricerca = ""; 


function isOrContains(node, container) {
    while (node) {
        if (node === container) {
            return true;
        }
        node = node.parentNode;
    }
    return false;
}

function elementContainsSelection(el) {
    var sel;
    if (window.getSelection) {
        sel = window.getSelection();
		if (sel.rangeCount > 0) {
            for (var i = 0; i < sel.rangeCount; ++i) {
                if (!isOrContains(sel.getRangeAt(i).commonAncestorContainer, el)) {
                    return false;
                }
            }
            return true;
        }
    } else if ( (sel = document.selection) && sel.type != "Control") {
        return isOrContains(sel.createRange().parentElement(), el);
    }
    return false;
}


function doSearch(text) {
    var sel;
	
	console.log("**** TIPO BROWSER" , navigator.appName , document.selection);
	
	$('#t1').hide();
	
	
    if (window.find && document.getSelection) {
        sel = document.getSelection();
        // sel = document.getElementById("drawing").getSelection()
		if (sel.rangeCount > 0) {
            sel.collapseToEnd();
        }
        window.find(text);
	}  
	else if (document.body.createTextRange) {
        if(document.selection) sel = document.selection;
		else sel = text ;
        var textRange;
       
		console.log(document.getSelection(text))
		if (sel.type == "Text") {
            textRange = sel.createRange();
            textRange.collapse(false);
        } else {
		
			textRange = document.body.createTextRange();
             textRange.collapse(true);
        }
       
	   if (textRange.findText(text)) {
            textRange.select();
        }
		
    }
	
	$('#t2').show();
	$('#t2').html($('#t1').val()) ; 
}


function reverse_visible(){
	$('#t1').show();
	$('#t2').hide();
}

function searchpage() {
    doSearch( document.getElementById("t1").value );
}

</script>	
<?php 
$tx_color = "#666" ; 
$bg_col = "#ddd";

//if($background_color) $bg_col = $background_color ;
//if($txt_color) $tx_color = $txt_color ;

?>
<div class="row" style="width: 100%; margin: 0px; margin-top: 0px; margin-bottom: 0px; background-color : #FFFFFF;text-align:right">
	<div class="col-xs-12"><input type="text" id="t1" name="t1" value=""/>
		<span style="width: 165px; border: #888 solid 1px ; display: inline-block; background-color : #fff;" id="t2"  onclick="reverse_visible()" ></span>
		<input id="button" type="button" value="FIND" name="b1" class="btn btn-info btn-xs" onclick="searchpage()" />
	</div>
	
	
	<div class="col-xs-6" style="text-align: right; "> 
		<!-- <a href="<?php echo base_path() ; ?>admin/test/index/<?php echo $id ; ?>" class="btn btn-info btn-xs" target="_blank">FullScreen</a> -->
		
	</div>
</div>

<!--<div class="row" style="width: 100%; margin: 0px; margin-top: 0px; padding-bottom: 5px;background-color : #FFFFFF">
	
	<div class="col-xs-12" style=" text-align: center ; font-size: 18pt ; color : <?php // echo $tx_color ; ?>; font-weight: bold ; "><?php
	?> &nbsp; <span 
	style=" display: inline-block; margin-right: 30px; margin-bottom : 0px; padding-botom: 0px;"><?php 
//		echo $identificativo ; 
	?></span></div> -->
</div>



<input type="hidden" name="prj_id" id="prj_id" value="<?php echo $id ; ?>">
<input type="hidden" name="area_select" id="area_select" value="0">

<div id="drawing" style="border: 0px solid #333; width: 100%; height:88vh;"></div>

<script src="<?php print $modulePath; ?>front/js/bootstrap.min.js"></script>
<script src="<?php print $modulePath; ?>front/js/bootstrap-dialog.min.js"></script>

<script src="<?php print $modulePath; ?>front/js/main.js"></script>
<script src="<?php print $modulePath; ?>front/js/svg.js"></script>
<script src="<?php print $modulePath; ?>front/js/slider.js"></script>
<script src="<?php print $modulePath; ?>front/js/pan_zoom_full.js"></script>

<script src="<?php print $modulePath; ?>front/js/draggy.js"></script>
<script src="<?php print $modulePath; ?>front/js/main.js"></script>

<script src="<?php print $modulePath; ?>front/js/context.js"></script>
<script src="<?php print $modulePath; ?>front/javascript.js"></script>
<script src="<?php print $modulePath; ?>front/js/vivus.js"></script>

</body>
</html>
