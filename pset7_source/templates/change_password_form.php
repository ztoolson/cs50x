<form action="change_password.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="current_password" placeholder="Current Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="new_password" placeholder="New Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="new_confirmation" placeholder="Confirm New Password" type="password"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Update</button>
        </div>
    </fieldset>
</form>
