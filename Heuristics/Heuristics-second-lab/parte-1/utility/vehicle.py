class Vehicle:
    def __init__(self, v_id: int, v_type: str, contains_freezer: bool) -> None:
        """Initialize a new Vehicle object.

        Args:
            v_id (int): Unique identifier for the vehicle.
            v_type (str): The type or model of the vehicle.
            contains_freezer (bool): Indicates whether the vehicle has a freezer (True) or not (False).
        """
        self.v_id: int = v_id
        self.v_type: str = v_type
        self.contains_freezer: bool = contains_freezer

    def __str__(self) -> str:
        """Create a string representation of the vehicle for the print function.

        Returns:
            str: A formatted string displaying the vehicle's ID, type, and freezer status.
        """
        # The freezer status is represented by 'C' if contains_freezer is True, 'X' if False.
        return f"{self.v_id}-{self.v_type}-{'C' if self.contains_freezer else 'X'}"
