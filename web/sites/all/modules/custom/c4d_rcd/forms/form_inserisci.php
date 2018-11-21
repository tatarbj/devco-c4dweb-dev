<form name="form_inserisci_elemento"  onsubmit="return false;" method="POST" action="#" id="form_inserisci_elemento">
<input type="hidden" name="tipologia" value="result">
<input type="hidden" name="vertical" value="0">
<input type="hidden" name="id_prj" id="id_prj" value="">
<div class="row">
	<div class="col-md-6">
		<label for="colonna_ele">Area: </label>
		<select name="colonna" id="colonna_ele" class="form-control"></select> 
		
		
		<label for="ordine_ele">Ordine: </label>
		<select name="ordine" class="form-control">
			<option value="0">Select</option>
			<?php
			for($x=0;$x<=100;$x++) { 
				echo "<option value=\"{$x}\">$x</option>\n";
			}
			?> 
		</select> 
		
		<label for="titolo">Titolo: </label>
		<textarea name="titolo" id="titolo" class="form-control" ></textarea>
		
		<br>
		
		<label for="descr">Descrizione: </label>
		<textarea name="descr" id="descr" class="form-control" style="height: 200px;"></textarea>
		
		<br>
		
	</div>
	<div class="col-md-6">
		
		<!-- 
		<label for="bg_color">Colore di sfondo: </label>
		<input type="text" class="form-control" id="bg_color" name="bg_color"> 
		-->
		
		<label for="bg_color">Colore di sfondo: </label>
		<div class="input-group">
			<div class="input-group-btn ">
				<button type="button" class="btn btn-default" id="bg_color" style="width: 50px;" name="bg_color">
					<span class="color-fill-icon dropdown-color-fill-icon" style="background-color:#000;"> &nbsp;  &nbsp; </span>
					&nbsp;<b class="caret"></b>
				</button>
				
			</div>
			<input type="text" name="bg_col" class="form-control" style="width: 150px;" id="bg_col" value="">
		</div>
		
		
		<label for="hovering">Hovering: </label>
		<textarea name="hovering" id="hovering" class="form-control" style="height: 200px;"></textarea>
	</div>
</div>


<input type="hidden" name="http_type" value="http://">
<input type="hidden" name="link_ele" value="">

</form>