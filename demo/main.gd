extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	print($HIVE_WALLET.get_private_key(0))
	print($HIVE_WALLET.get_private_key(1))
	print($HIVE_WALLET.get_private_key(2))
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	pass

