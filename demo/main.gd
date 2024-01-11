extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	#print($HIVE_WALLET.get_private_key(0))
	#print($HIVE_WALLET.get_private_key(1))
	#print($HIVE_WALLET.get_private_key(2))
	
	$HIVE.call_deferred("get_profile","bflanagin")
	
	pass # Replace with function body.
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	pass



func _on_hive_error(type, data):
	var box = $RichTextLabel
	box.append_text("from Error")
	box.append_text(str(type))
	box.append_text(" ")
	box.append_text(str(data)+"\n")
	pass # Replace with function body.


func _on_hive_recieved_profile(json):
	var box = $RichTextLabel
	box.append_text("\nFrom recieved profile")
	box.append_text(str(json))	
	pass # Replace with function body.
