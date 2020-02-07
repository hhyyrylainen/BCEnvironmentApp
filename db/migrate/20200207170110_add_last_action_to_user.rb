class AddLastActionToUser < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :last_action, :timestamp
  end
end
